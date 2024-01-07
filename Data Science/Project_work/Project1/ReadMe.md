### Mini Project 1
### Exploratory Data Analysis of flight Data from Booking Websites
#### Objectives
The objective of this step is to collect useful flight information from flight aggregator webpages in a format that can be preprocessed for analysis.
Flight features such as, flight duration, number of layovers, layover durations, flight departure and arrival time, airplane type, bag types allowed, and others are extracted from the booking sites.

Three aggregating websites were scraped and preprocessed for analysis. The data was analyzed using several visualizations and the following questions can be answered with the visuals.
1.	What is the price range of flights on 18th December 2023?
2.	What is the total duration of flights that are available?
3.	What is the minimum no of layovers for flights available?
4.	What is the price range of flights for a specific number of layovers?
5.	What are the airlines that is available?
6.	What is the ratio of direct to flights with layovers?
7.	Are flights with layovers cheaper than direct flight?
The final stage was to provide a user interface that will enable easy querying of the data. 


#### Repository Files 
- First_Mini_project_1.ipynb: This is the main file of this project. it contains the script used to achieve the each step of the project(this is from webscrapping to data analysis).
- Project1_Report_Motunrayo_Ibiyo.pdf: This is a short report of the project.
- CSV files: this is a saved version of the information scrapped from the web page at the time the project was completed. The CSV file was introduced to reduce the time spent scrapping the website and
   also help make the project usable even when the DOM of the websites changes.
#### Project Sections

##### Data Collection: Scrapping the Website
Three websites were scraped for information of flights available on the 18th Deccember 2023 from Helsinki, Finland to Manchester, United kindom. 
The websites scraped were Booking.com, Kayak.com and Momondo.com with 70, 146, and 143 records obtained from each of them respectively. in total 359 records were obtained from the websites.
The libraries used for web scrapping include
- Selenium
- Beautiful soup
- Selenium-stealth
Booking.com:  ![image](https://github.com/Motunrayo244/EDISS-MP/assets/42592153/5ecb93c3-c4e4-40ef-8bd3-7a45ed9c2803)   
Kayak: ![image](https://github.com/Motunrayo244/EDISS-MP/assets/42592153/4a75c2d2-c4de-44c6-96cc-9428e0d9c98f) 
Momondo: ![image](https://github.com/Motunrayo244/EDISS-MP/assets/42592153/72ed843d-3334-4b34-8c6c-bd2d5f9eb4a8)



##### Data Preprocessing
In this stage, the data from all websites are manipulated to get similar features.
This involves the extraction of features from the initial data format. Cleaning the data, and ensuring that each column represents a single feature.

The data for booking.com had 6 columns about the flight and one column for the website name before preprocessing. After preprocessing, 25 flight features were obtained giving 26 features in total.

##### Exploratory Data Analysis
This section analysis the extracted data. 
- a high percentage of flights to Manchester United Kingdom on the 18 left before 14:00.
- flights with 3 layovers had a cost between $200, 00 and $500, 00.
More info about the insights from the analysis is report file.
![image](https://github.com/Motunrayo244/EDISS-MP/assets/42592153/8d4edd6d-04b5-44ca-ba98-5708971fa265)

##### Interactive User Interface

+ the user  to perform the following task to give the user the list of “ideal” flight to the chosen city:  
+ The user inputs certain preferences for the flight, e.g., price ranges, trip duration ranges (how long from departure to destination), whether the flight is direct or has one or more stops (if it has stops then layover duration), flight company from available options etc.
  + price range
  + duration range
  + direct vs with stops
  + if with stops then layover duration
  + flight airline from available option


+  The first stage allows users to specify price range, duration range, airlines, if direct flight only, if layover is allowed and others filter criteria.
+   This returns records of data that fits into the criteria provided sorted by a user defined feature. 


![image](https://github.com/Motunrayo244/EDISS-MP/assets/42592153/d07a468e-d651-45a0-a4ab-44c495471c92)

+ The user is then allowed to streamline this search again by providing a range of departure time, airline, and total flight duration.
+  This stage returns information about the cheapest and the fastest (shortest duration) flight that is within all the filter criteria. in the second widget.



![image](https://github.com/Motunrayo244/EDISS-MP/assets/42592153/0cd4a945-e537-46c6-8ea7-0099ce705620)
##### Improvement
Despite the challenges highlighted, the project can be improved in several ways. 
1.	Addition of other booking sites. 
2.	Removal of duplicate flight information from the three websites.
3.	Furthermore, more filter criteria like baggage allowance (cabin and checked bags), layover city can be added to the filter options available in the user interface.


