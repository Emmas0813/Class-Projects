// Emma Smith
// Data Structures - Spring 2023
// Project 2

#include <iostream>
#include <string>
#include <fstream> // for reading fileInput

using namespace std;

class tableException{ //various display messages for different exceptions
public:
	tableException(){} // default constructor
	void recordNotFound(){
		cout << "Record not found"<< endl;
	}
	void valueNotFound(){
		cout << "Value not found" << endl;
	}
	void columnOutOfBounds(int c){
		cout << "Column Number " << c << " out of bounds" << endl;
	}
	void rowOutOfBounds(int r){
		cout << "Row Number " << r << " out of bounds" << endl;
	}
	void nonNumericColumnType(){
		cout << "Column not numeric" << endl;
	}
};
class tableClass {
protected:
	string** myTable; // 2D string array to store all values (strings and numbers)
	string* DTarray; // 1D array to store the data types of each column
	int noRows, noCols; // number of rows and columns

public:
	//Constructors
	tableClass();
	tableClass(int rows, int cols);
	
	// Overload the [] operator to access a row in myTable
	string* operator[](int i); 

	//File reading Method
	void readCSV(string filename);
	
	//Initialize DTArray method
	void storeD(int numCol);

	//Output Method
	void display();

	//Sort the table
	void sortTable();

	//Search record
	string* searchRecord(string str); // str will be from the first column

	//Search value from table
	void searchValue(string str);
	
	//Getters
	int getNumberRows();// returns the number of rows
	int getNumberCols();// returns the number of columns
	tableClass* getColumns(int colLeft, int colRight); // returns a tableClass with a set of columns from colLeft to colRight indices
	tableClass* getRows(int rowTop, int rowBottom); // returns a tableClass with a set of rows from rowTop to rowBottom indices
	tableClass* getRowsCols(int colLeft, int colRight, int rowTop, int rowBottom); // returns a tableClass with the data between the cols and rows given

	//Find info of a given column
	double findMin(int colNumber); // returns the min of the given column

	//Destructor
	~tableClass();
};
tableClass::tableClass(){
	noCols = 0;
	noRows = 0;
	myTable = NULL;
	DTarray = NULL;
}
tableClass::tableClass(int rows, int cols){
	noRows = rows;
	noCols = cols;
	myTable = new string* [rows];
	for(int i = 0; i < rows; i++){ // create columns for 2d array
		myTable[i] = new string[cols];
	}
	DTarray = new string[cols];
}
string* tableClass::operator[](int i){
	return myTable[i]; // return the specified row in myTable
}
void trim(string& str) { // function used to trim trailing whitespaces
    size_t end = str.find_last_not_of(" \t\r\n"); 
    if(end != string::npos) { // if the last part of the line is a white space, delete it
        str.erase(end + 1);
    }
}
void tableClass::readCSV(string filename){
	ifstream personInfo; // new object from ifstream class called personInfo
	personInfo.open(filename); // open CSV file 
	string* temp = new string[noRows * noCols]; // temp 1d array to store info
	int count = 0; //counter to traverse temp

	while(personInfo.peek()!=EOF){ // read till end of file
		string info; // variable to store info in
		for(int i = 0; i < noCols - 1; i++){
			getline(personInfo, info, ','); // for every string separated by a comma, store it in info.
			trim(info); // trim any trailing whitespaces
			temp[count] = info; // store value into temp array
			count++;
		}
		getline(personInfo, info, '\n');
		trim(info); // for every string separated by newline, store it in info.
		temp[count] = info; // store value into temp array
		count++;	
	} 
	count = 0; // set counter back to 0;
	personInfo.close();
	for(int i = 0; i < noRows; i++){ // store temp array into myTable 2d array
		for(int j = 0; j < noCols; j++){
			myTable[i][j] = temp[count];
			count++; // increment counter to get next temp array variable
		}
	}
	delete[] temp;
}
void tableClass::storeD(int numCol){
	for(int i = 0; i < numCol; i++){ // read the data types from text file and assign to DTarray
		cin >> DTarray[i];
	}
}
void tableClass::display(){
	for(int i = 0; i < noCols; i++){ // display data types
		cout << DTarray[i] << " ";
	}
	cout << endl;
	for(int i = 0; i < noRows; i++){ // display contents of 2d array
		for(int j = 0; j < noCols; j++){
			cout << myTable[i][j] << "  ";
		}
		cout << endl;
	}
}
void tableClass::sortTable(){
	for(int i = 0; i < noRows; i++){
		for(int j = 0; j < noRows - i - 1; j++){ // compare all rows
			if(myTable[j][0].compare(myTable[j+1][0]) > 0){ // compare the two strings 
				for(int k = 0; k < noCols; k++){
					swap(myTable[j][k], myTable[j + 1][k]); // swap the row if previous string is greater than following string
				}
			}
		}
	}
}
string* tableClass::searchRecord(string str){
	for(int i = 0; i < noRows; i++){
		if(myTable[i][0] == str){ // if record found, return entire row
			return myTable[i];
		}
	}
	return NULL; //otherwise, return null
}
void tableClass::searchValue(string str){
	bool found = false; // boolean flag to keep track if value is found or not.
	cout << "Searching for " << str << endl;
	for(int i = 0; i < noRows; i++){
		for(int j = 0; j < noCols; j++){
			if(myTable[i][j] == str){ // if value is found, display its coordinates.
				cout << " found in (" << i << ", " << j << ")" << endl; 
				found = true; // change "found" to true.
			}
		}
	}
	try{ // if value not found, handle exception
		if(!found){
			throw tableException();//throw exception
		}
	} catch(tableException te){ // catch the exception and display message.
		te.valueNotFound();
	}
}
int tableClass::getNumberRows(){
	return noRows;
}
int tableClass::getNumberCols(){
	return noCols;
}
tableClass* tableClass::getColumns(int colLeft, int colRight){
	int cols = abs(colRight - colLeft + 1);// calculate columns and handle possibility of negative number
	tableClass* table = new tableClass(noRows, cols); // create new tableClass object 
	for(int i = colLeft; i < colRight; i++){ // display data types for limited columns
		cout << DTarray[i] << " ";
	}
	for(int i = 0; i < noRows; i++){
		for(int j = colLeft; j < colRight; j++){
			table->myTable[i][j - colLeft] = myTable[i][j]; // assign table values from myTable in specified columns
		}
	}
	return table;// return tableClass object
}
tableClass* tableClass::getRows(int rowTop, int rowBottom){
	int rows = abs(rowBottom - rowTop); // calculate rows and handle possibility of negative number
	tableClass* table = new tableClass(rows, noCols); // create new tableClass object
	for(int i = 0; i < noCols; i++){ // display data types of columns
		cout << DTarray[i] << " ";
	}
	for(int i = rowTop; i < rowBottom; i++){ // traverse array between specified rows
		for(int j = 0; j < noCols; j++){ 
			table->myTable[i-rowTop][j] = myTable[i][j]; // assign table values from myTable at specified rows.
		}
	}
	return table;// return tableClass object
}
tableClass* tableClass::getRowsCols(int colLeft, int colRight, int rowTop, int rowBottom){//TODO: fix this
	int rows = abs(rowBottom - rowTop + 1);// calculate rows and handle possibility of negative number
	int cols = abs(colRight - colLeft + 1);// calculate columns and handle possibility of negative number
	tableClass* table = new tableClass(rows, cols); // create tableClass object of new size of specified rows & columns
	for(int i = colLeft; i < colRight; i++){ // display data types of columns
		cout << DTarray[i] << " ";
	}
	for(int i = rowTop; i < rowBottom; i++){ // traverse array between specified rows & columns
		for(int j = colLeft; j < colRight; j++){ 
			table->myTable[i - rowTop][j - colLeft] = myTable[i][j]; // assign table values from myTable at specified rows & columns.
		}
	}
	return table; // return tableClass object
}
double tableClass::findMin(int colNumber){
    try{
		double min = stod(myTable[1][colNumber]); // convert string to double from std::stod
    	if (colNumber <= noCols){ // if colNumber is out of bounds
        	for (int i = 1; i < noRows; i++) {
           	 	if (stod(myTable[i][colNumber]) < min){  // check proceeding values
                	min = stod(myTable[i][colNumber]); //store smallest value into min
            	}
        	}
			return min;
    	}
	} catch(invalid_argument& e){ // if the column is nonnumeric, catch exception
		cout << "Column type is not numeric" << endl;
	}
}
tableClass::~tableClass(){
	for(int i = 0; i < noRows; i++){ // delete dynamic 2d array myTable
		delete[] myTable[i];
	}
	delete[] DTarray; // delete DTArray
	delete[] myTable;
}
int main(){
	int numRows, numCols;
	string fileName;
	char option;
	string temp;
	int num;
	int r1, r2, c1, c2;

	cin >> numRows >> numCols >> fileName;
	cout << "NumRows: " << numRows << endl;
	cout << "NumCols: " << numCols << endl;
	cout << "FileName: " << fileName << endl;

	tableClass* d = new tableClass(numRows, numCols);

	d->readCSV(fileName); 
	d->storeD(numCols); // read the data types and store in DTarray of d
	d->sortTable(); // sort the table

	while(!cin.eof()){
		cin >> option; // read option
		if(option == 'F' && !cin.eof()){ // search for given record
			cin >> temp; // read "record"
			string* t = d->searchRecord(temp); // store the "row" in temp value t.
			try{
				if(t!= NULL){ // check if tableClass object was returned from function
					cout << "Record found: " << endl << "\t";
					for(int i = 0; i < numCols; i++){ // display the row of given record
						cout << t[i] << " ";
					}
					cout << endl;
				}
				else{
					throw tableException();
				}
			} catch(tableException te){ //catch exception and display message
				te.recordNotFound();
			}
		}
		else if(option == 'V' && !cin.eof()){ // search for given value
			cin >> temp; // read "value"
			d->searchValue(temp); 
		}
		else if(option == 'D' && !cin.eof()){ // display the sorted table
			d->display();
		}
		else if(option == 'I' && !cin.eof()){ // find the minimum value of the given column number
			cin >> num;
			try{
				if(num > numCols){
					throw tableException();
				} else{
					double i = d->findMin(num);
					cout << "Min of " << num << " is " << i << endl;
				}
			} catch(tableException te){
				if(num > numCols){
					te.columnOutOfBounds(num);
				} else{
					te.nonNumericColumnType();
				}
			}
			
		}
		else if(option == 'C' && !cin.eof()){ // display the table between two given columns, inclusively.
			cin >> c1 >> c2;
			tableClass* c = d->getColumns(c1, c2); //assign t to tableClass object of restricted size
			c->display();
			delete c;
		}
		else if(option == 'R' && !cin.eof()){ // display the table between two given rows, not inclusively.
			cin >> r1 >> r2;
			tableClass* r = d->getRows(r1, r2); //assign t to tableClass object of restricted size
			r->display();
			delete r;
		}
		else if(option == 'S' && !cin.eof()){ // // display the table between two given rows & two given columns, not inclusively.
			cin >> c1 >> c2 >> r1 >> r2; // read "rows and columns"
			tableClass* s = d->getRowsCols(c1, c2, r1, r2); //assign t to tableClass object of restricted size
			s->display();
			delete s;
		}
	}
	d->~tableClass(); // call destructor
	return 0;
}