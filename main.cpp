#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <memory_resource>
using namespace std;

//Function to read csv file and to store the contents
void read_CSV_file(const string& filename, vector<vector<string>>& data) {
    //opening the file
    ifstream file(filename);
    string line;

    //Error checking, to check if the file opened
    if (!file.is_open()) {
        cout << "Unable to open file " << filename << endl;
        return;
    }
    //Reading the file line by line
    while (getline(file, line)) {

        //Split the lin into cells
        stringstream ss(line);
        string cell;
        vector<string> row;

        //Reading each cell in the line
        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        //Adding a new row to the data vector
        data.push_back(row);
    }
    //Closing the file
    file.close();
}

//Struct to represent a team
struct Team {
    string team_name;
    string local_town;
    string stadium;
};

//Struct to represent a fixture
struct Fixture {
    Team home_team;
    Team away_team;
    int leg;
    int weekend;
    string time;
};

struct weekend {
    Fixture matches[2];
};

//Function to generate fixtures for a list of teams
vector<Fixture> generate_fixtures(const vector<Team>& teams) {
    //Initialize the fixtures vector
    vector<Fixture> fixtures;

    //Calculate the number of teams and weekends
    int num_of_teams = teams.size();
    int num_of_weekends = (num_of_teams *(num_of_teams - 1)) / 2;

    //Generate fixtures for each pair of teams
    for (int i=0; i<num_of_teams; i++) {
        for (int j=i+1; j<num_of_teams; j++) {

            //Check if the teams are from the same local town
            if (teams[i].local_town == teams[j].local_town) {
                //Calculate the weekend number
                int weekend = num_of_weekends - (num_of_teams - 1) + j - i;

                //Add the fixture to the fixture vector
                fixtures.push_back({teams[i], teams[j], 1, weekend});
                fixtures.push_back({teams[j], teams[i], 2, weekend + 1});
            } else {

                //Calculate the weekend number
                int weekend = (i * (num_of_teams - 1)) + j - i;

                //Add the fixture to the fixture vector
                fixtures.push_back({teams[i], teams[j], 1, weekend,});
                fixtures.push_back({teams[j], teams[i], 2, weekend + 1});
            }
        }
    }
    //Return the fixtures vector
    return fixtures;
}

//Funtion to display fixtures to console
void display_fixtures(const vector<Fixture>& fixtures) {
    //Print a header
    cout << "The Generated Fixtures: " << endl;

    //Display each fixture
    for (const auto& fixture : fixtures) {
        //Print the weekend number
        cout << "Weekend: " << fixture.weekend << endl;

        //Print the leg number
        cout << "Leg: " << fixture.leg << endl;

        //Print the time
        cout << "Time: " << fixture.time << endl;

        //Print the teams
        cout << fixture.home_team.team_name << " VS " << fixture.away_team.team_name << endl;

        //Print the stadium
        cout << "Stadium: " << fixture.home_team.stadium << endl;

        //Print the local town
        cout << "Local Town: " << fixture.home_team.local_town << endl;
        cout << endl;
    }
}

//Function to write fixtures to a CSV file
void write_fixtures_to_csv(const vector<Fixture>& fixtures, const string& filename) {
    //Creat the csv file name
    string csvFilename = filename + ".csv";

    //Open the file
    ofstream file(filename);

    //Write the header
    file << "Weekend,Leg,Time,Home team,Away team,Stadium,Local town" << endl;

    //Write each fixture
    for (const auto& fixture : fixtures) {
        //Write the weekend number
        file  << fixture.weekend << ","

        //Write the leg number
        << fixture.leg << ","

        //Write the time
        << fixture.time << ","

        //Write the home team
        << fixture.home_team.team_name<< ","

        //Write the away team
        << fixture.away_team.team_name << ","

        //Write the stadium
        << fixture.home_team.stadium << ","

        //Write the local town
        << fixture.home_team.local_town << "\n";
    }

    //Close the file
    file.close();
}
int main()
{
    //Read the teams from a csv file
    vector<vector<string>> data;
    read_CSV_file("C:/Users/Bee/CLionProjects/untitled17/teams_csvFile.csv", data);

    //Print the teams
    for (const auto& row : data) {
        for (const auto& cell : row) {
            cout << cell << " ";
        }
        cout << endl;

    }

   //convert data to teams
    vector<Team> teams;
    for (const auto& row : data) {
        Team team;
        team.team_name = row[0];
        team.local_town = row[1];
        team.stadium = row[2];
        teams.push_back(team);
    }

    //Generate fixtures for the teams
    vector<Fixture> fixtures = generate_fixtures(teams);

    //Display the fixtures
    display_fixtures(fixtures);

    //Write the fixtures to a csv file
    string fixturesFilename = "C:/Users/Bee/Documents/new.csv";
    write_fixtures_to_csv(fixtures, fixturesFilename);
    string fixtures_string;
    return 0;
    }