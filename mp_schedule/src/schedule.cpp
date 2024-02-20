/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

// version 1.01 updated at 5/1/2023 1745
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "schedule.h"
#include "utils.h"
#include <algorithm>

using namespace std;
/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename){
    // Your code here!
    V2D result_;
    string data_ = file_to_string(filename);
    vector<string> temp_rows;
    split_string(data_, '\n',temp_rows);
    for (unsigned i=0; i<temp_rows.size();i++){
        vector<string> temp_row;
        split_string(temp_rows[i],',',temp_row);
        for (unsigned j=0; j<temp_row.size();j++){
            temp_row[j] = trim(temp_row[j]);
        }
        result_.push_back(temp_row);
    }
    return result_;


}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(const V2D & cv, const V2D & student){
    // YOUR CODE HERE
    V2D corrected_roster;
    V2D roster_by_stu;
    for (unsigned i=0; i<cv.size();i++){
        vector<string> row;
        string course_name = cv[i][0];
        row.push_back(course_name);
        for (unsigned j=0; j<student.size(); j++){
            for (unsigned k=1; k<student[j].size();k++){
                if (student[j][k]==course_name){
                    row.push_back(student[j][0]);
                    break;
                }
            }
        }
        roster_by_stu.push_back(row);
        
    }
    for (unsigned i=0; i<cv.size();i++){
        vector<string> row;
        for (unsigned j=1; j<cv[i].size(); j++){
            string student_name = cv[i][j];
            for (unsigned k=1;k<roster_by_stu[i].size();k++){
                if (roster_by_stu[i][k]==student_name){
                    if (row.empty()){
                        row.push_back(cv[i][0]);
                    }
                    row.push_back(student_name);
                    break;
                }
            }
        }
        if (!row.empty()){
            corrected_roster.push_back(row);
        }
    }


    return corrected_roster;


}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots){
    // Your code here!
    vector <int> status(courses.size(),0);
    vector<vector<int>> adjmatrix_ = adjmatrix(courses);
    V2D schedule_;
    unsigned index = 0;
    for (unsigned i=0;i<courses.size();i++){
        if (status[i]==0){
            if(i != 0){
                index = index+1;
            }
            if (index >= timeslots.size()){
                V2D returnval;
                vector<string> row_;
                row_.push_back("-1");
                returnval.push_back(row_);
                return (returnval);
            }            
            vector<string> row;
            row.push_back(timeslots[index]);
            row.push_back(courses[i][0]);
            status[i]=1;
            vector<unsigned> in_row;
            in_row.push_back(i); 

            

            for(unsigned j=i+1; j<courses.size();j++){
                if(adjmatrix_[i][j]==0 && status[j]==0){
                    // row.push_back(courses[j][0]);
                    // status[j]=1;
                    int flag = 0;
                    for (auto k : in_row){
                        if(adjmatrix_[k][j]==1){
                            flag = 1;
                            break;
                        }
                    }
                    if (flag==0){
                        row.push_back(courses[j][0]);
                        status[j]=1;
                        in_row.push_back(j);
                    }
                }
            }
            schedule_.push_back(row);
        }
    }
    cout << "schedule size " << schedule_.size() << endl;
    cout << "slots size " << timeslots.size() << endl;
    //cout << index << endl;
    if(index < timeslots.size()-1){
        //cout << "triggered_" << endl;
        while (index<timeslots.size()-1){
            //cout << "triggered" << endl;
            index = index+1;
            vector<string> row;
            row.push_back(timeslots[index]);
            schedule_.push_back(row);

        }
    }

    return schedule_;


}

vector<vector<int>> adjmatrix(const V2D &courses){
    vector<vector<int>> adjmatrix(courses.size(),vector<int>(courses.size(),0));
    for (unsigned i=0; i<courses.size()-1; i++){
        for (unsigned j=i+1 ; j<courses.size();j++){
            int flag = 0;
            unsigned index = 1;
            while (flag == 0 && index < courses[i].size()){
                auto temp1 = courses[i][index];
                for (unsigned k=1; k<courses[j].size();k++){
                    if (temp1 == courses[j][k]){
                        flag = 1;
                        adjmatrix[i][j] = 1;
                        adjmatrix[j][i] = 1;
                        break;
                    }
                }
                index = index + 1;
            }
        }
    }
    for(vector<int> elem: adjmatrix){
        for(int ele: elem){
            cout<< ele << ' ';
        }
        cout << endl;
    }

    return adjmatrix;
}

