#include <Arduino.h>
#include <TensorFlowLite.h>
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "model.h"  
#include "four.h"

const int numSamples = 119;
int samplesRead = numSamples;

tflite::AllOpsResolver tflOpsResolver;

const tflite::Model* tflModel = nullptr;
tflite::MicroInterpreter* tflInterpreter = nullptr;
TfLiteTensor* tflInputTensor = nullptr;
TfLiteTensor* tflOutputTensor = nullptr;

constexpr int tensorArenaSize = 24 * 1024;  // Adjusted from 10 * 1024
uint8_t tensor_arena[tensorArenaSize];

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Get the TFL representation of the model byte array
  tflModel = tflite::GetModel(model);  // Ensure this matches your quantized model array
  if (tflModel->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Model provided is schema version is not equal to supported version!");
    return;
  }

  // Create a MicroInterpreter instance.
  tflInterpreter = new tflite::MicroInterpreter(tflModel, tflOpsResolver, tensor_arena, tensorArenaSize, nullptr);

  // Allocate memory for the model's input and output tensors
  if (tflInterpreter->AllocateTensors() != kTfLiteOk) {
    Serial.println("AllocateTensors() failed");
    return;
  }

  // Get pointers for the model's input and output tensors
  tflInputTensor = tflInterpreter->input(0);
  tflOutputTensor = tflInterpreter->output(0);

  if (tflInputTensor == nullptr || tflOutputTensor == nullptr) {
    Serial.println("Input or output tensor not initialized!");
    return;
  }

  // Print input tensor size
  Serial.print("Input tensor size: ");
  Serial.println(tflInputTensor->bytes);

  // Print input tensor dimensions
  Serial.print("Input tensor dimensions: ");
  for (int i = 0; i < tflInputTensor->dims->size; i++) {
    Serial.print(tflInputTensor->dims->data[i]);
    if (i < tflInputTensor->dims->size - 1) {
      Serial.print(" x ");
    }
  }
  Serial.println();

  // Print benchmark image size
  Serial.print("Benchmark image size: ");
  Serial.println(sizeof(image_data) / sizeof(image_data[0]));

  Serial.println("Setup complete.");
}

void loop() {
  // Ensure the image data size matches the input tensor dimensions (28x28)
  if (sizeof(image_data) / sizeof(image_data[0]) != 28 * 28) {
    Serial.println("Original image data size does not match expected size!");
    delay(5000); // Delay to prevent flooding the serial monitor
    return;
  }

  // Print tensor data type for debugging
  Serial.print("Input tensor type: ");
  Serial.println(tflInputTensor->type);

  // Directly assign the input image data
  if (tflInputTensor->type == kTfLiteUInt8) {
    for (int i = 0; i < 28 * 28; i++) {
      tflInputTensor->data.uint8[i] = static_cast<uint8_t>(image_data[i]);
    }
  } else {
    Serial.println("Unsupported input tensor type!");
    return;
  }


  // Run the model on the input and make sure it succeeds.
  if (tflInterpreter->Invoke() != kTfLiteOk) {
    Serial.println("Invoke failed!");
    return;
  }

  // Print output tensor values for debugging
  Serial.println("Output tensor values:");
  for (int i = 0; i < tflOutputTensor->dims->data[1]; i++) {
    Serial.print(tflOutputTensor->data.uint8[i]);
    Serial.print(" ");
  }
  Serial.println();

  // Find the index of the highest scoring category.
  int max_index = 0;
  float max_value = -128.0;  // Initialize to a very low value for int8
  float output_scale = tflOutputTensor->params.scale;
  int output_zero_point = tflOutputTensor->params.zero_point;

  for (int i = 0; i < tflOutputTensor->dims->data[1]; i++) {
    float value = (tflOutputTensor->data.uint8[i] - output_zero_point) * output_scale;
    if (value > max_value) {
      max_value = value;
      max_index = i;
    }
  }

  // Print the classification results.
  Serial.print("Image: ");
  Serial.println("four.h");  // Replace with actual image name if available
  Serial.print("Class: ");
  Serial.println(max_index);
  Serial.print("Probability: ");
  Serial.println(max_value);

  // Wait before running inference again.
  delay(5000);
}
