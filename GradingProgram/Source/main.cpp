#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <algorithm>

int createClassSize()
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(18, 25); // define the range

	int classSize = distr(gen);

	return classSize;
}

int countLines(std::ifstream& filename)
{
	std::string line;
	int numLines = 0;
	while (getline(filename, line))
	{
		numLines++;
	}
	filename.clear();
	filename.seekg(0);
	return numLines;
}

std::string randomClass(std::ifstream& filename, int fileSize)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, fileSize); // define the range

	int classLineNum = distr(gen);

	std::string line;
	std::string className;
	int lineNum = 0;
	while (getline(filename, line))
	{
		if (lineNum == classLineNum)
		{
			className = line;
		}
		lineNum++;
	}
	filename.clear();
	filename.seekg(0);
	return className;
}

class Students
{
public:
	std::string studentName;
	int studentGradeLevel;
	float studentGrade;
	std::string studentGender;
	std::vector<std::string> assignmentNames;
	std::vector<int> assignmentScores;
	std::vector<int> assignmentPoints;

};

void createStudents(Students studentList[], int& classSize, int& numBoys, int& numGirls)
{
	std::ifstream boynames("C:/VisualStudioProjects/GradingProgram/GradingProgram/Source/boynames.txt");
	int boyNamesSize = countLines(boynames);
	std::ifstream girlnames("C:/VisualStudioProjects/GradingProgram/GradingProgram/Source/girlnames.txt");
	int girlNamesSize = countLines(girlnames);
	std::ifstream lastnames("C:/VisualStudioProjects/GradingProgram/GradingProgram/Source/lastnames.txt");
	int lastNamesSize = countLines(lastnames);

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> boys(1, boyNamesSize); // define the range
	std::uniform_int_distribution<> girls(1, girlNamesSize); // define the range
	std::uniform_int_distribution<> last(1, lastNamesSize); // define the range

	std::vector<int> boysNamesLines;
	std::vector<int> girlsNamesLines;
	std::vector<int> lastNamesLines;

	for (int i = 0; i < numBoys; i++)
	{
		int boyNameLine = boys(gen);
		bool differentLine = false;
		while (!differentLine)
		{
			if (std::find(boysNamesLines.begin(), boysNamesLines.end(), boyNameLine) != boysNamesLines.end())
			{
				boyNameLine = boys(gen);
			}
			else
			{
				differentLine = true;
			}
		}
		boysNamesLines.push_back(boyNameLine);
	}
	for (int i = 0; i < numGirls; i++)
	{
		int girlNameLine = girls(gen);
		bool differentLine = false;
		while (!differentLine)
		{
			if (std::find(girlsNamesLines.begin(), girlsNamesLines.end(), girlNameLine) != girlsNamesLines.end())
			{
				girlNameLine = girls(gen);
			}
			else
			{
				differentLine = true;
			}
		}
		girlsNamesLines.push_back(girlNameLine);
	}
	for (int i = 0; i < classSize; i++)
	{
		int lastNameLine = last(gen);
		bool differentLine = false;
		while (!differentLine)
		{
			if (std::find(lastNamesLines.begin(), lastNamesLines.end(), lastNameLine) != lastNamesLines.end())
			{
				lastNameLine = last(gen);
			}
			else
			{
				differentLine = true;
			}
		}
		lastNamesLines.push_back(lastNameLine);
	}

	std::vector<std::string> boysNamesVector;
	std::vector<std::string> girlsNamesVector;
	std::vector<std::string> lastNamesVector;
	std::string name;
	int i = 0;
	while (getline(boynames, name))
	{
		i++;
		if (std::find(boysNamesLines.begin(), boysNamesLines.end(), i) != boysNamesLines.end())
		{
			boysNamesVector.push_back(name);
		}
	}

	i = 0;
	while (getline(girlnames, name))
	{
		i++;
		if (std::find(girlsNamesLines.begin(), girlsNamesLines.end(), i) != girlsNamesLines.end())
		{
			girlsNamesVector.push_back(name);
		}
	}

	i = 0;
	while (getline(lastnames, name))
	{
		i++;
		if (std::find(lastNamesLines.begin(), lastNamesLines.end(), i) != lastNamesLines.end())
		{
			std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });
			name[0] = toupper(name[0]);
			lastNamesVector.push_back(name);
		}
	}
	auto rng = std::default_random_engine{ rd() };
	std::shuffle(std::begin(lastNamesVector), std::end(lastNamesVector), rng);

	for (int i = 0; i < numBoys; i++)
	{
		studentList[i].studentName = boysNamesVector[i] + " " + lastNamesVector[i]; 
		studentList[i].studentGradeLevel = 11;
		studentList[i].studentGender = "Male";
		studentList[i].studentGrade = 0;
	}
	for (int i = numBoys; i < classSize; i++)
	{
		studentList[i].studentName = girlsNamesVector[i-numBoys] + " " + lastNamesVector[i];
		studentList[i].studentGradeLevel = 11;
		studentList[i].studentGender = "Female";
		studentList[i].studentGrade = 0;
	}
	boynames.close();
	girlnames.close();
	lastnames.close();
}

int main()
{
	int classSize = createClassSize();
	std::ifstream classList("C:/VisualStudioProjects/GradingProgram/GradingProgram/Source/classList.txt");
	int classListSize = countLines(classList);
	std::string className = randomClass(classList, classListSize);
	classList.close();
	
	int lowerLimitSize = (classSize / 2) - 1;
	int upperLimitSize = (classSize / 2) + 2;
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(lowerLimitSize, upperLimitSize); // define the range

	int numBoys = distr(gen);
	int numGirls = classSize - numBoys;
	int numAssignments = 0;

	//std::cout << "Boys: " << numBoys << " - Girls: " << numGirls << std::endl;

	std::vector<Students> studentList(classSize);
	createStudents(studentList.data(), classSize, numBoys, numGirls);

	auto rng = std::default_random_engine{ rd() };
	std::shuffle(std::begin(studentList), std::end(studentList), rng);

	std::cout << "Class successfully created." << std::endl;
	std::string userCommand;
	while (true)
	{
		std::cout << ">> ";
		getline(std::cin, userCommand);
		std::transform(userCommand.begin(), userCommand.end(), userCommand.begin(), [](unsigned char c) { return std::tolower(c); });
		if (userCommand == "#quit")
		{
			std::cout << std::endl;
			std::cout << "<<====== Closing program... ======>>" << std::endl;
			break;
		}
		else if (userCommand == "#view class" || userCommand == "#viewclass")
		{
			std::cout << std::endl;
			std::cout << "<<=====================================>>" << std::endl;
			std::cout << "Class Name: " << className << std::endl;
			std::cout << "Class Size: " << classSize << std::endl;
			std::cout << "Student List: " << std::endl;
			for (int i = 0; i < classSize; i++)
			{
				std::cout << i + 1 << ". " << studentList[i].studentName << " - " << studentList[i].studentGradeLevel << " - " << studentList[i].studentGender << std::endl;
			}
			std::cout << "<<=====================================>>" << std::endl;
			std::cout << std::endl;
		}
		else if (userCommand == "#enter grade" || userCommand == "#entergrade")
		{
			std::cout << std::endl;
			std::cout << "<<=== Select the student ===>>" << std::endl;
			std::cout << ">> ";
			std::string profileInput;
			int profileNum;
			while (true)
			{
				getline(std::cin, profileInput);
				try {
					profileNum = std::stoi(profileInput);
					break;
				}
				catch (...) {
					std::cout << "<<============= Invalid Number ==============>>" << std::endl;
				}
			}
			std::cout << "<<=== Select the assignment ===>>" << std::endl;
			std::cout << ">> ";
			std::string assignmentInput;
			int assignmentNum;
			while (true)
			{
				getline(std::cin, assignmentInput);
				try {
					assignmentNum = std::stoi(assignmentInput);
					break;
				}
				catch (...) {
					std::cout << "<<============= Invalid Number ==============>>" << std::endl;
				}
			}
			std::cout << "<<=== Enter the student's score ===>>" << std::endl;
			std::cout << ">> ";
			std::string scoreInput;
			int scoreNum;
			while (true)
			{
				getline(std::cin, scoreInput);
				try {
					scoreNum = std::stoi(scoreInput);
					break;
				}
				catch (...) {
					std::cout << "<<============= Invalid Number ==============>>" << std::endl;
				}
			}
			studentList[profileNum - 1].assignmentScores[assignmentNum - 1] = scoreNum;
			float totalPoints = 0;
			float totalScore = 0;
			float overallGrade;
			for (int i = 0; i < numAssignments; i++)
			{
				totalPoints += studentList[profileNum - 1].assignmentPoints[i];
				totalScore += studentList[profileNum - 1].assignmentScores[i];
			}
			overallGrade = (totalScore / totalPoints) * 100;
			studentList[profileNum - 1].studentGrade = overallGrade;
			std::cout << "<<=== Successfully graded " << studentList[profileNum - 1].studentName << "'s assignment '" << studentList[profileNum - 1].assignmentNames[assignmentNum - 1] << "'" << std::endl;
			std::cout << std::endl;
			
		}
		else if (userCommand == "#grade assignment" || userCommand == "#gradeassignment")
		{
			std::cout << std::endl;
			std::cout << "<<=== Select the assignment ===>>" << std::endl;
			std::cout << ">> ";
			std::string assignmentInput;
			int assignmentNum;
			while (true)
			{
				getline(std::cin, assignmentInput);
				try {
					assignmentNum = std::stoi(assignmentInput);
					break;
				}
				catch (...) {
					std::cout << "<<============= Invalid Number ==============>>" << std::endl;
				}
			}
			for (int i = 0; i < classSize; i++)
			{
				std::cout << "<<=== Enter " << studentList[i].studentName << "'s score ===>>" << std::endl;
				std::cout << ">> ";
				std::string scoreInput;
				int scoreNum;
				while (true)
				{
					getline(std::cin, scoreInput);
					try {
						scoreNum = std::stoi(scoreInput);
						break;
					}
					catch (...) {
						std::cout << "<<============= Invalid Number ==============>>" << std::endl;
					}
				}
				studentList[i].assignmentScores[assignmentNum - 1] = scoreNum;
				float totalPoints = 0;
				float totalScore = 0;
				float overallGrade;
				for (int i = 0; i < numAssignments; i++)
				{
					totalPoints += studentList[i].assignmentPoints[i];
					totalScore += studentList[i].assignmentScores[i];
				}
				overallGrade = (totalScore / totalPoints) * 100;
				studentList[i].studentGrade = overallGrade;
				std::cout << "<<=== Successfully graded " << studentList[i].studentName << "'s assignment '" << studentList[i].assignmentNames[assignmentNum - 1] << "'" << std::endl;
				std::cout << std::endl;
			}
		}
		else if (userCommand == "#create assignment" || userCommand == "#createassignment")
		{
			std::string assignmentName;
			std::cout << std::endl;
			std::cout << "<<==== What do you want to call this assignment? ====>>" << std::endl;
			std::cout << ">> ";
			getline(std::cin, assignmentName);
			std::cout << std::endl;
			std::string assignmentWorth;
			std::cout << "<<======== How many points will it be worth? ========>>" << std::endl;
			int assignmentPoints;
			while (true)
			{
				getline(std::cin, assignmentWorth);
				try {
					assignmentPoints = std::stoi(assignmentWorth);
					break;
				}
				catch (...) {
					std::cout << "<<============= Invalid Number ==============>>" << std::endl;
				}   
			}

			for (int i = 0; i < classSize; i++)
			{
				studentList[i].assignmentNames.push_back(assignmentName);
				studentList[i].assignmentScores.push_back(0);
				studentList[i].assignmentPoints.push_back(assignmentPoints);
			}
			
			std::cout << "<<========= Assignment successfully created =========>>" << std::endl;
			std::cout << std::endl;
			numAssignments++;
		}
		else if (userCommand == "#view assignments" || userCommand == "#viewassignments")
		{
			std::cout << std::endl;
			std::cout << "<<==== Assignment List ====>>" << std::endl;
			for (int i = 0; i < numAssignments; i++)
			{
				std::cout << i + 1 << ". " << studentList[0].assignmentNames[i] << " - " << studentList[0].assignmentPoints[i] << " Points" << std::endl;
			}
			std::cout << "<<=========================>>" << std::endl;
			std::cout << std::endl;
		}
		else if (userCommand == "#profile")
		{
			std::cout << std::endl;
			std::string profileInput;
			int profileNum;
			std::cout << "Which profile would you like to view? ";
			while (true)
			{
				getline(std::cin, profileInput);
				try {
					profileNum = std::stoi(profileInput);
					break;
				}
				catch (...) {
					std::cout << "<<============= Invalid Number ==============>>" << std::endl;
				}   
			}
			std::cout << "<<==== " << studentList[profileNum - 1].studentName << "'s Profile ====>>" << std::endl;
			std::cout << "Name: " << studentList[profileNum - 1].studentName << std::endl;
			std::cout << "Grade: " << studentList[profileNum - 1].studentGradeLevel << std::endl;
			float totalPoints = 0;
			float totalScore = 0;
			float overallGrade;
			for (int i = 0; i < numAssignments; i++)
			{
				totalPoints += studentList[profileNum - 1].assignmentPoints[i];
				totalScore += studentList[profileNum - 1].assignmentScores[i];
			}
			overallGrade = (totalScore / totalPoints)*100;
			studentList[profileNum - 1].studentGrade = overallGrade;
			std::cout << "Gender: " << studentList[profileNum - 1].studentGender << std::endl;
			if (studentList[profileNum - 1].studentGrade < 60)
			{
				std::cout << "Grade: " << "F (" << studentList[profileNum - 1].studentGrade << "%)" << std::endl;
			}
			else if (studentList[profileNum - 1].studentGrade < 64)
			{
				std::cout << "Grade: " << "D- (" << studentList[profileNum - 1].studentGrade << "%)" << std::endl;
			}
			else if (studentList[profileNum - 1].studentGrade < 67)
			{
				std::cout << "Grade: " << "D (" << studentList[profileNum - 1].studentGrade << "%)" << std::endl;
			}
			else if (studentList[profileNum - 1].studentGrade < 70)
			{
				std::cout << "Grade: " << "D+ (" << studentList[profileNum - 1].studentGrade << "%)" << std::endl;
			}
			else if (studentList[profileNum - 1].studentGrade < 74)
			{
				std::cout << "Grade: " << "C- (" << studentList[profileNum - 1].studentGrade << "%)" << std::endl;
			}
			else if (studentList[profileNum - 1].studentGrade < 77)
			{
				std::cout << "Grade: " << "C (" << studentList[profileNum - 1].studentGrade << "%)" << std::endl;
			}
			else if (studentList[profileNum - 1].studentGrade < 80)
			{
				std::cout << "Grade: " << "C+ (" << studentList[profileNum - 1].studentGrade << "%)" << std::endl;
			}
			else if (studentList[profileNum - 1].studentGrade < 84)
			{
				std::cout << "Grade: " << "B- (" << studentList[profileNum - 1].studentGrade << "%)" << std::endl;
			}
			else if (studentList[profileNum - 1].studentGrade < 87)
			{
				std::cout << "Grade: " << "B (" << studentList[profileNum - 1].studentGrade << "%)" << std::endl;
			}
			else if (studentList[profileNum - 1].studentGrade < 90)
			{
				std::cout << "Grade: " << "B+ (" << studentList[profileNum - 1].studentGrade << "%)" << std::endl;
			}
			else if (studentList[profileNum - 1].studentGrade < 94)
			{
				std::cout << "Grade: " << "A- (" << studentList[profileNum - 1].studentGrade << "%)" << std::endl;
			}
			else if (studentList[profileNum - 1].studentGrade < 100)
			{
				std::cout << "Grade: " << "A (" << studentList[profileNum - 1].studentGrade << "%)" << std::endl;
			}
			else
			{
				std::cout << "Grade: " << "A+ (" << studentList[profileNum - 1].studentGrade << "%)" << std::endl;
			}
			std::cout << "Assignments:" << std::endl;
			for (int i = 0; i < numAssignments; i++)
			{
				std::cout << i + 1 << ". " << studentList[profileNum - 1].assignmentNames[i] << " - " << studentList[profileNum - 1].assignmentScores[i] << "/" << studentList[profileNum - 1].assignmentPoints[i] << std::endl;
			}
			std::cout << "<<=========================>>" << std::endl;
			std::cout << std::endl;
		}
		else
		{
			std::cout << "<<====== Invalid Command. ======>>" << std::endl;
		}
	}

	return 0;
}