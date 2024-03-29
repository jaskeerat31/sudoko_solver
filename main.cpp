/*
 *=====================
 *   Sudoku Solver
 *=====================
 * Takes in sudoku puzzle and outputs the solution
*/

#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;

/**
  *	This class provides a data structure which can hold and manipulate the values in a sudoku puzzle.
  *	In this file, we shall call this data structure the 'Sudoku Frame'.
*/
class SudokuFrame{

	int sudokuFrame[9][9]; //This pointer will hold all the values in the matrix.
	int editableFrame[9][9]; //This pointer will tell us all the values which are editable.


	public:SudokuFrame(){
		menu();
	}

	/**
	  *	Displays a menu to the user when the SudokuFrame objects in instantiated
	  *	(which is basically at the start of the program) to display all possible options
	  *	from the user.
	*/
	private:void menu(){

		cout<<"\n======================\n";
		cout<<"    Sudoku Solver\n";
		cout<<"======================\n\n";

		cout<<"Welcome to Sudoku Solver!\n";
		cout<<"Before we start, you will have to input the puzzle into this program.\n\n";
		cout<<"You can either:-\n";
		cout<<"\t1. Input the puzzle by entering the values manually. (Enter 1)\n";
		cout<<"\t2. Input the puzzle by reading a file with values in it. (Enter 2)\n";
		cout<<"\t   The file must not have a name > 20 characters.\n";
		cout<<"\t   The file must be in the same directory as this C++ file.\n";
		cout<<"\t   The file must have all 81 values seperated with spaces.\n";
		cout<<"\t   Blank cells must be filled in as 0 (eg; 1 0 0 2 0 0 ...).\n";
		cout<<"\t   --> ";

		int option;
		cin>>option;

		if(option==1) readFrameValues();
		else if(option==2) readFrameValuesFile();
		else{
			while(true){
				cout<<"\nYou seem to have entered an invalid option. Try again.\n";
				cout<<"\t   --> ";
				cin>>option;

				if(option==1) readFrameValues();
				else if(option==2) readFrameValuesFile();
				else continue;

				break;
			}
		}

	}

	
	  //Reads the values for the Sudoku Frame cell-by-cell.
	 
	private:void readFrameValues(){
		cout<<"\nEnter the specified value when prompted.\n";
		cout<<"Enter 0 if cell is empty.\n\n";

		int rowIter, colIter;

		for(rowIter=0; rowIter<9; rowIter++){ //Iterating over cells to read vals.
			for(colIter=0; colIter<9; colIter++){
				int enteredValue;

				cout<<"Enter value for cell["<<rowIter+1<<"]["<<colIter+1<<"] --> ";
				cin>>enteredValue;

				if(!(enteredValue>=0 && enteredValue<=9)){ //Checking for bounds in input.
					while(true){ //We loop until valid input is read from user.
						cout<<"Oops! You seem to have entered a wrong value! Try again.\n";
						cout<<"Enter value for cell ["<<rowIter+1<<"]["<<colIter+1<<"] --> ";
						cin>>enteredValue;

						if(enteredValue>=0 && enteredValue<=9) break;
					}
				}

				sudokuFrame[rowIter][colIter]=enteredValue;

				if(enteredValue==0) editableFrame[rowIter][colIter]=0;
				else editableFrame[rowIter][colIter]=1;
			}
			cout<<"-------\n"; //Display a break after every row for convenience.
		}
	}

	  //Reads the values from a file containing the frame values seperated by whitespaces.
	 
	private:void readFrameValuesFile(){

		char filename[30]; //Getting filename.

		cout<<"\nEnter the name of the file that contains the Sudoku Puzzle.\n";
		cout<<"\t   --> ";
		cin>>filename;

		ifstream sudokuFile; //Opening file for reading.
		sudokuFile.open(filename,ios::in);

		int rowIter, colIter;

		for(rowIter=0; rowIter<9; rowIter++){ //Iterating over file values.
			for(colIter=0; colIter<9; colIter++){
				int readValue;

				sudokuFile>>readValue;

				if(!(readValue>=0 && readValue<=9)){ //Checking bounds for input.
					cout<<"\nValue "<<((rowIter*9)+colIter+1)<<" in "<<filename;
					cout<<" seems to be wrong! Correct the value and try again!\n";
					exit(EXIT_FAILURE);
				}

				sudokuFrame[rowIter][colIter]=readValue;

				if(sudokuFrame[rowIter][colIter]==0) editableFrame[rowIter][colIter]=0;
				else editableFrame[rowIter][colIter]=1;

				if(sudokuFile.eof()) break; //Breaking if EOF is reached.
			}
		}

		sudokuFile.close();
	}

	
	   //Assigns the passed-in number to the specified row and col.
	
	public:void setCellValue(int row, int col, int num){
		if(editableFrame[row][col]==0) sudokuFrame[row][col]=num;
	}

	  //Returns the value of the cell at the specified row and col.
	
	public:int getCellValue(int row, int col){
		int cellValue=sudokuFrame[row][col];
		return cellValue;
	}

	/**
	  *	Returns 0/1 depending on editableFrame values.
	  *	takes row,col of required cell as parameters
	*/
	public:int isEditable(int row, int col){
		return (editableFrame[row][col]-1)*(-1);
	}

	/**
	  *	Clears frame of all values, other than the question values, from
	  *	the specified cell to the last cell.
	  *	takes row,col of specified cell as parameters
	*/
	public:void clearFrameFrom(int row, int col){
		int jcount=0;
		int rowIter, colIter;

		for(rowIter=row; rowIter<9; rowIter++){

			if(jcount==0) colIter=col;
			else colIter=0;

			for(; colIter<9; colIter++){
				if(editableFrame[rowIter][colIter]==0) sudokuFrame[rowIter][colIter]=0;
			}

			jcount++;

		}
	}

	  //Displays the values stored in the frame
	  
	public:void displayFrame(){

		cout<<"=====================================++";
		int rowIter, colIter;

		for(rowIter=0; rowIter<9; rowIter++){
			int cellIter=1;

			cout<<"\n";
			for(colIter=0; colIter<9; colIter++){
				if(cellIter==3){
					cout<<sudokuFrame[rowIter][colIter]<<" ";
					cout<<" ";
					cellIter=1;
				}
				else{
					cout<<sudokuFrame[rowIter][colIter]<<"  ";
					cellIter++;
				}
			}

			if(rowIter%3!=2) cout<<"\n";
			else cout<<"\n";
		}

	}

};


/**
  *	This class provides a very simple way to iterate through
  *	the possibilities of a specified cell. This object utilises linked lists.
*/
class Possibilities{

	struct node{
		int value;
		struct node* next;
	}; //The struct for the node

	typedef struct node* Node;

	Node head; //The head node
	Node pos; //A node iterator variable

	  //This constructor initialises the head node.
	
	public:Possibilities(){
		head=new struct node;
		head->next=NULL;
	}

	/**
	  *	This destructor destroys the linked list once the object
 	  *	has finished its lifespan. Calls the destroy() function.
	*/
	public:~Possibilities(){
		destroy();
	}

	  //This functions takes in a number and adds it as a node in linked list
	
	public:void append(int number){
		Node temp=new struct node;

		temp->value=number;
		temp->next=NULL;

		pos=head;
		while(pos!=NULL){
			if(pos->next==NULL){
				pos->next=temp;
				break;
			}
			pos=pos->next;
		}
	}

	/**
	  *	An operator overload function which overloads the [] operator.
	  *	takes the index of the required node in linked list as parameter
	  *	returns the value contained in the specified node.
	*/
	public:int operator[](int index){
		int count=0;
		pos=head->next;

		while(pos!=NULL){
			if(count==index)
				return pos->value;
			pos=pos->next;
			count++;
		}

		return -1;
	}

	  //Prints the values inside all the nodes of the linked list.
	  
	public:void print(){
		pos=head->next;
		while(pos!=NULL){
			cout<<pos->value<<",";
			pos=pos->next;
		}
		cout<<"\b";
	}

	
	 //Returns the length of the linked list.
	  
	public:int length(){
		pos=head->next;
		int count=0;

		while(pos!=NULL){
			count++;
			pos=pos->next;
		}

		return count;
	}

	/**
	  *	This function takes in a possibilities object and copies
	  *	the contents into THIS object.
	  *  	takes the possibilities object which is to be copied as a parameter
	*/
	public:void copy(Possibilities possibilities){ 
		int oldLength=possibilities.length();
		int iter=0;

		pos=head;
		for(iter=0; iter<oldLength; iter++){
			Node temp=new struct node;

			temp->next=NULL;
			temp->value=possibilities[iter];

			pos->next=temp;
			pos=pos->next;
		}
	}

	
	 //Frees all the nodes in the linked list.
	
	private:void destroy(){
		Node temp;
		pos=head;
		while(pos!=NULL){
			temp=pos;
			pos=pos->next;
			delete temp;
		}
	}

};


/**
  *	Takes in the SudokuFrame object and solves the Sudoku Puzzle.
*/
class SudokuSolver{

	int recursiveCount; //Stats variable
	SudokuFrame frame; //The frame object

	/**
	  *	The constructor initialises the recursiveCount variable and also calls
	  *	the solve() function which solves the puzzle. It also displays the frames
	  *	before and after the solving.
	*/
	public:SudokuSolver(){
		recursiveCount=0;

		cout<<"\nCalculating possibilities...\n";
		cout<<"Backtracking across puzzle....\n";
		cout<<"Validating cells and values...\n\n";

		solve();
		cout<<"Congratulations Your puzzle has been solved!\n\n";
		displayFrame();

		cout<<"\n\n";
	}

	/**
	  *	Checks if the value in the specified cell is valid or not.
	  *	takes row,col of the required value and the required value as parameters
	  *	returns whether the value is valid or not in the sudoku frame
	*/
	private:bool cellValueValid(int row, int col, int currentValue){
		int rowIter, colIter;

		//Checking if value exists in same column
		for(rowIter=0; rowIter<9; rowIter++){
			if(rowIter!=row){
				int comparingValue=frame.getCellValue(rowIter,col);
				if(comparingValue==currentValue) return false;
			}
		}

		//Checking if value exists in same row
		for(colIter=0; colIter<9; colIter++){
			if(colIter!=col){
				int comparingValue=frame.getCellValue(row,colIter);
				if(comparingValue==currentValue) return false;
			}
		}

		//Checking if value exists in the same 3x3 square block
		if(ThreeByThreeGridValid(row,col,currentValue)==false) return false;

		return true;
	}

	/**
	  *	Checks if the same value is also present in the same 3x3 grid block.
	  *	takes row,col of required cell and the required value as parameters
	  *	returns whether the value is present or not
	*/
	private:bool ThreeByThreeGridValid(int row, int col, int currentValue){
		int rowStart=(row/3)*3;
		int rowEnd=(rowStart+2);

		int colStart=(col/3)*3;
		int colEnd=(colStart+2);

		int rowIter, colIter;

		for(rowIter=rowStart; rowIter<=rowEnd; rowIter++){
			for(colIter=colStart; colIter<=colEnd; colIter++){
				if(frame.getCellValue(rowIter,colIter)==currentValue) return false;
			}
		}

		return true;
	}

	/**
	  *	Gets the possible values and assigns them to the possibilities list.
	  *	takes row and col of specified cell as parameters
	  *	returns Possibilities object containing all the possible values.
	*/
	private:Possibilities getCellPossibilities(int row, int col){
		int iter=0;

		Possibilities possibilities;

		for(iter=1; iter<=9; iter++){
			if(cellValueValid(row,col,iter)==true)
				possibilities.append(iter);
		}

		return possibilities;
	}

	/**
	  *	The recursive function which does all the work, this iterates over the
	  *	possible values for the specified cell one-by-one. Once a value has been filled, it
	  *	goes to the next cell. Here, the same thing happens. If none of the possible values
	  *	work out, then the function backtracks to the previous cell.
  	  *
	  *	takes row and col of specified cell as parameters
	  *	returns whether the value put in the cell made it a SUCCESS or NOT
	*/
	private:int singleCellSolve(int row, int col){

		statsIncrement(); //This is used to see how many times the func is called.

		if(frame.isEditable(row,col)==true){

			Possibilities possibilities;
			possibilities.copy(getCellPossibilities(row,col));

			int posLength=possibilities.length();
			int posIter=0, newRow=row, newCol=col;

			for(posIter=0; posIter<posLength; posIter++){ //We iter over the possible values
				int possibility=possibilities[posIter];
				frame.setCellValue(row,col,possibility);

				//We now increment the col/row values for the next recursion
				if(col<8) newCol=col+1;
				else if(col==8){
					if(row==8) return 1; //this means success
					newRow=row+1;
					newCol=0;
				}

				{

					if(singleCellSolve(newRow,newCol)==0){ //If wrong, clear frame and start over
						frame.clearFrameFrom(newRow,newCol);
					}
					else return 1;

				} //Recursion block ends here

			} //Loop ends here

			return 0;

		} //The isEditable() if block ends here.
		else{

			int newRow=row, newCol=col;

			//Same incrementing of the col/row values
			if(col<8) newCol=col+1;
			else if(col==8){
				if(row==8) return 1;
				newRow=row+1;
				newCol=0;
			}

			return singleCellSolve(newRow,newCol);

		} //The else block ends here

	}


	 //Calls the singleCellSolve() func and prints a success/fail mesg.
	  
	private:void solve(){
		int success=singleCellSolve(0,0);
	}

	//displays the sudoku frame
	private:void displayFrame(){
		frame.displayFrame();
	}

	//increments the count variable to keep track of the recursions occured
	private:void statsIncrement(){
		recursiveCount++;
	}

	public:void statsPrint(){
		cout<<"\nThe singleCellSolve() function was recursively called "<<recursiveCount<<" times.\n";
	}

};

//driver function for sudoku solver
int main(){
	SudokuSolver ss;
	return 0;
}
