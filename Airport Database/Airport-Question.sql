--Which stores have over 50 employees? 
SELECT * FROM Store WHERE numEmployees > 50 ORDER BY storeType;

--Which store has the highest customer capacity? 
SELECT MAX(capacity) FROM Store; 

--What are the longest flights which depart from Terminal A?
SELECT departureLocation,  lengthOfFlight  FROM Flight 
WHERE departureLocation = 'Terminal A' 
GROUP BY departureLocation, lengthOfFlight 
HAVING lengthOfFlight > '02:00:00' AND departureLocation = 'Terminal A'; 

--What are the loyalty programs for United Airlines and JetBlue?   
SELECT loyaltyProgram FROM Airline 
WHERE companyName IN ('United Airlines', 'JetBlue'); 

--What is the average number of seats at a gate? 
SELECT AVG(numSeats) 
FROM Gate; 

--How many flights fly out of Terminal B? 
SELECT COUNT(*) 
FROM Flight 
WHERE departureLocation = 'Terminal B'; 

--Which stores have a higher than average capacity for each terminal? 
SELECT storeID, terminal, capacity 
FROM Store S 
WHERE S.capacity >  
	(SELECT AVG(capacity) 
	FROM Store 
	WHERE terminal = S.terminal);
    
--What is the maximum store capacity? 
SELECT MAX(capacity) 
FROM Store; 

--How many of each kind of worker are on a flight if the airplane model is a Boeing 747? 
SELECT aircraftModel, numPilots, numStewards FROM Airplane 
INNER JOIN Airline ON Airplane.airline = Airline.companyName 
WHERE Airplane.aircraftModel = 'Boeing 747';  

--How many bathrooms are near the stores in Terminal A? 
SELECT Store.storeType, Terminal.numRestrooms 
FROM Terminal 
INNER JOIN Store ON Terminal.name =  Store.terminal 
WHERE Terminal.name = 'A'; 
