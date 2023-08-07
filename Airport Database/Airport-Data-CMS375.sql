INSERT INTO Terminal 
VALUES('A', 4, 5, 3), 
	('B', 4, 5, 3);

INSERT INTO Airline (companyName, loyaltyProgram, avgFlightPerDay, numPilots, numStewards) 
VALUES('Southwest Airlines', 'Rapid Rewards', 5600.25, 2, 4), 
	('American Airlines', 'AAdvatage', 4945.50, 2, 3), 
	('Delta Air Lines', 'SkyMiles', 4017.75, 1, 2),
    ('JetBlue', 'TrueBlue', 5600.25, 2, 4), 
	('United Airlines', 'Mileage Plus', 4945.50, 2, 3), 
	('Spirit', 'Free Spirit', 4017.75, 1, 2);

INSERT INTO Flight (flightNumber, airline, lengthOfFlight, destination, departureLocation) 
VALUES (2490, 'JetBlue', '05:23:00', 'San Francisco, California', 'Terminal B'), 
	(2658, 'United Airlines', '02:55:00', 'Dallas, Texas', 'Terminal A'), 
	(3320, 'Southwest Airlines', '02:40:00', 'New York, New York', 'Terminal A'), 
	(2975, 'Spirit', '05:05:00', 'Las Vegas, Nevada', 'Terminal A'), 
	(9075, 'American Airlines', '05:30:00', 'Los Angeles, California', 'Terminal B'), 
	(3754, 'Delta Air Lines', '01:10:00', 'Miami, Florida', 'Terminal A');

INSERT INTO Airplane(airline, aircraftModel, seats, restrooms, exits) 
VALUES('JetBlue', 'Boeing 747', 150, 2, 4), 
	('United Airlines', 'Boeing 737', 140, 2, 4), 
	('Spirit', 'Boeing 727', 120, 2, 4);

INSERT INTO Store (terminal, location, capacity, storeType, numEmployees)
VALUES ('A', 'Near Terminal A security', 40, 'Tech on the go', 15), 
	('A', 'Between Terminal A and Gates', 15, 'Duty Free Store', 10), 
	('A', 'Between Terminal A and Gates', 60, 'Barnes and Noble', 30), 
	('A', 'Near the last Gate', 50, 'McDonald’s', 110), 
	('A', 'Near the last Gate', 10, 'Starbucks', 25), 
	('B', 'Near Terminal B security', 120, 'Universal Orlando Store', 75), 
	('B', 'Between Terminal B and Gates', 55, 'Hudson News', 35), 
	('B', 'Between Terminal B and Gates', 80, 'Orlando Market', 65), 
	('B', 'Near the last Gate', 64, 'Oakley Store', 32), 
	('B', 'Near the last Gate', 98, 'Burger King', 42);

INSERT INTO Security 
VALUES ('A', 40, 3, 1), 
	('B', 55, 2, 2);

INSERT INTO Transportation
VALUES (118, 200, 'A or B', 'A or B', 'A'), 
	(50, 100, 'A or B', 'A or B', 'B');

INSERT INTO Gate (gateID, numSeats, arriving) 
VALUES ('A1', 150, 0),  
	('A2', 135, 0), 
	('A3', 78, 1), 
	('A4', 125, 1), 
	('A5', 58, 0), 
	('B1', 150, 1), 
	('B2', 89, 0), 
	('B3', 112, 0), 
	('B4', 98, 1), 
	('B5', 120, 0);

INSERT INTO GateAssignment
VALUES (1234, 'A1'),
	(1235, 'A2'),
	(1236, 'B1');
