CREATE TABLE Airline( 
	companyName VARCHAR(20) PRIMARY KEY NOT NULL, 
	loyaltyProgram VARCHAR(20), 
	avgFlightPerDay DOUBLE, 
	numPilots SMALLINT UNSIGNED, 
	numStewards SMALLINT UNSIGNED 
);
CREATE TABLE Terminal ( 
	name VARCHAR(2) PRIMARY KEY NOT NULL,
	numGates TINYINT UNSIGNED,
	numStores TINYINT UNSIGNED,
	numRestrooms TINYINT UNSIGNED 
); 
CREATE TABLE Airplane( 
	airplaneID INT UNSIGNED PRIMARY KEY NOT NULL AUTO_INCREMENT, 
	airline VARCHAR(20), 
	aircraftModel VARCHAR(30), 
	seats TINYINT UNSIGNED, 
	restrooms TINYINT UNSIGNED, 
	exits TINYINT UNSIGNED, 
	FOREIGN KEY (airline) REFERENCES Airline(companyName) 
);
CREATE TABLE Store (  
	storeID SMALLINT UNSIGNED PRIMARY KEY AUTO_INCREMENT, 
	terminal VARCHAR(2),
	location VARCHAR(30), 
	capacity TINYINT UNSIGNED, 
	storeType VARCHAR(30), 
	numEmployees TINYINT UNSIGNED, 
	FOREIGN KEY (terminal) REFERENCES Terminal(name) 
); 
CREATE TABLE Security (
	location  VARCHAR(2) PRIMARY KEY, 
	numEmployees SMALLINT UNSIGNED, 
	numRegularLines TINYINT UNSIGNED, 
	numPreCheckLines TINYINT UNSIGNED, 
	FOREIGN KEY (location) REFERENCES Terminal(name) 
); 
CREATE TABLE Transportation (
	tramID TINYINT UNSIGNED PRIMARY KEY, 
	capacity SMALLINT UNSIGNED, 
	pickUpLocation VARCHAR(30), 
	dropOffLocation VARCHAR(30), 
	terminal VARCHAR(2),
	FOREIGN KEY (terminal) REFERENCES Terminal(name) 
); 
CREATE TABLE Flight ( 
	flightNumber INT UNSIGNED PRIMARY KEY NOT NULL, 
	airline VARCHAR(20), 
	lengthOfFlight TIME, 
	destination VARCHAR(50), 
	departureLocation VARCHAR(50), 
	FOREIGN KEY (airline) REFERENCES Airline(companyName) 
); 
CREATE TABLE Gate ( 
	gateID VARCHAR(4) PRIMARY KEY NOT NULL, 
	numSeats TINYINT UNSIGNED, 
	arriving TINYINT UNSIGNED CHECK (arriving = 0 OR arriving = 1) 
); 
CREATE TABLE GateAssignment ( 
	flight INT UNSIGNED PRIMARY KEY NOT NULL, 
	gateID VARCHAR(4) NOT NULL, 
	FOREIGN KEY (gateID) REFERENCES Gate(gateID) 
); 
