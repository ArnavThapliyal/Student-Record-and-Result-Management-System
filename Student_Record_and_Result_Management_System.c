#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LENGTH 50
#define EMAIL_LENGTH 100
#define PHONE_LENGTH 15

typedef struct 
{
    char sap_id[10];
    char roll_no[10];
    char name[NAME_LENGTH];
    char phone[PHONE_LENGTH];
    char email[EMAIL_LENGTH];
    int year;
    int semester;
    float sgpa[8]; // SGPA for 8 semesters
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

void add_student();
void search_student();
void calculate_cgpa();
void average_cgpa_per_year();
void display_all_students();
void delete_student();
void display_students_by_sap_id();
void display_students_by_name();
void display_student_detiails()
{
    printf("----------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-10s | %-10s | %-30s | %-15s | %-30s | %-5s | %-8s |\n", 
           "SAP ID", "Roll No", "Name", "Phone", "Email", "Year", "Semester");
    printf("----------------------------------------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < student_count; i++) 
    {
        printf("| %-10s | %-10s | %-30s | %-15s | %-30s | %-5d | %-8d |\n", 
               students[i].sap_id, 
               students[i].roll_no, 
               students[i].name, 
               students[i].phone, 
               students[i].email, 
               students[i].year, 
               students[i].semester);
    }
    
    printf("----------------------------------------------------------------------------------------------------------------------------------\n");
}

int main() 
{
    int choice;

    do 
    {
        printf("\nStudent Record and Result Management System\n");
        printf("1. Add Student\n");
        printf("2. Search Student\n");
        printf("3. Calculate CGPA\n");
        printf("4. Average CGPA per Year\n");
        printf("5. Display All Students\n");
        printf("6. Delete Student\n");
        printf("7. Display Students by SAP ID\n");
        printf("8. Display Students by Name\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) 
        {
            case 1: add_student(); break;
            case 2: search_student(); break;
            case 3: calculate_cgpa(); break;
            case 4: average_cgpa_per_year(); break;
            case 5: display_all_students(); break;
            case 6: delete_student(); break;
            case 7: display_students_by_sap_id(); break;
            case 8: display_students_by_name(); break;
            case 9: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 9);

    return 0;
}

void add_student() 
{
    if (student_count >= MAX_STUDENTS) 
    {
        printf("ERROR: Maximum limit reached.\n");
        return;
    }

    Student new_student;
    printf("Enter SAP ID: ");
    scanf("%s", new_student.sap_id);
    printf("Enter Roll No: ");
    scanf("%s", new_student.roll_no);
    printf("Enter Name: ");
    scanf(" %[^\n]", new_student.name);
    printf("Enter Phone No: ");
    scanf("%s", new_student.phone);
    printf("Enter Email ID: ");
    scanf("%s", new_student.email);

    while (1) 
    {
        printf("Enter Year (1-4): ");
        scanf("%d", &new_student.year);
        if (new_student.year >= 1 && new_student.year <= 4) 
        {
            break;
        }
        printf("Invalid year! Please enter a value between 1 and 4.\n");
    }

    while (1) 
    {
        printf("Enter Semester (1-8): ");
        scanf("%d", &new_student.semester);
        if ((new_student.year == 1 && (new_student.semester >= 1 && new_student.semester <= 2)) ||
            (new_student.year == 2 && (new_student.semester >= 3 && new_student.semester <= 4)) ||
            (new_student.year == 3 && (new_student.semester >= 5 && new_student.semester <= 6)) ||
            (new_student.year == 4 && (new_student.semester >= 7 && new_student.semester <= 8))) 
        {
            break;
        }
        printf("Invalid semester for the given year! Please enter a valid semester.\n");
    }

    for (int i = 0; i < 8; i++) 
    {
        if (i < new_student.semester) 
        {
            printf("Enter SGPA for Semester %d: ", i + 1);
            scanf("%f", &new_student.sgpa[i]);
            if (new_student.sgpa[i] < 0 || new_student.sgpa[i] > 10) 
            {
                printf("Invalid SGPA! Please enter a value between 0 and 10.\n");
                i--;
            }
        } 
        else 
            new_student.sgpa[i] = 0.0;
    }

    students[student_count++] = new_student;
    printf("Student added successfully!\n");
}

void search_student() 
{
    char sap_id[10];
    printf("Enter SAP ID to search: ");
    scanf("%s", sap_id);
    
    printf("----------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-10s | %-10s | %-30s | %-15s | %-30s | %-5s | %-8s |\n", 
           "SAP ID", "Roll No", "Name", "Phone", "Email", "Year", "Semester");
    printf("----------------------------------------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < student_count; i++) 
    {
        if (strcmp(students[i].sap_id, sap_id) == 0) 
        {
            printf("| %-10s | %-10s | %-30s | %-15s | %-30s | %-5d | %-8d |\n", 
                students[i].sap_id, 
                students[i].roll_no, 
                students[i].name, 
                students[i].phone, 
                students[i].email, 
                students[i].year, 
                students[i].semester);
            printf("----------------------------------------------------------------------------------------------------------------------------------\n");
            for (int j = 0; j < 8; j++) 
                printf("SGPA for Semester %d: %.2f\n", j + 1, students[i].sgpa[j]);
            
            return;
        }
    }
    printf("Student with SAP ID %s not found.\n", sap_id);

}

void calculate_cgpa() 
{
    for (int i = 0; i < student_count; i++) 
    {
        float total_sgpa = 0;
        for (int j = 0; j < 8 ; j++) 
            total_sgpa += students[i].sgpa[j];
        
        float cgpa = total_sgpa / 8;
        printf("CGPA for Student %s: %.2f\n", students[i].name, cgpa);
    }
}

void average_cgpa_per_year() 
{
    float total_cgpa[5] = {0}; 
    int student_count_per_year[5] = {0};

    for (int i = 0; i < student_count; i++) 
    {
        float total_sgpa = 0;
        int completed_semesters = 0;
        for (int j = 0; j < 8; j++) 
        {
            if (students[i].sgpa[j] > 0) 
            {
                total_sgpa += students[i].sgpa[j];
                completed_semesters++;
            }
        }
        float cgpa = total_sgpa / 8;
        total_cgpa[students[i].year - 1] += cgpa;
        student_count_per_year[students[i].year - 1]++;
    }

    for (int i = 0; i < 4; i++) 
    {
        if (student_count_per_year[i] > 0) 
            printf("Average CGPA for Year %d: %.2f\n", i + 1, total_cgpa[i] / student_count_per_year[i]);

        else 
            printf("No students in Year %d.\n", i + 1);
        
    }
}

void display_all_students() 
{
    if (student_count == 0) 
    {
        printf("No student records available.\n");
        return;
    }

    printf("List of All Students:\n");
    display_student_detiails();

}

void delete_student() 
{
    char sap_id[10];
    printf("Enter SAP ID of the student to delete: ");
    scanf("%s", sap_id);

    for (int i = 0; i < student_count; i++) 
    {
        if (strcmp(students[i].sap_id, sap_id) == 0) 
        {
            for (int j = i; j < student_count - 1; j++) 
                students[j] = students[j + 1];

            student_count--;
            printf("Student with SAP ID %s deleted successfully.\n", sap_id);
            return;
        }
    }
    printf("Student with SAP ID %s not found.\n", sap_id);
}

void display_students_by_sap_id()
{
    if (student_count == 0) 
    {
        printf("No student records available.\n");
        return;
    }

    // Simple bubble sort 
    for (int i = 0; i < student_count - 1; i++) 
    {
        for (int j = 0; j < student_count - i - 1; j++) 
        {
            if (strcmp(students[j].sap_id, students[j + 1].sap_id) > 0) 
            {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("\nStudents sorted by SAP ID:\n");
    display_student_detiails();
}

void display_students_by_name() 
{
    if (student_count == 0) 
    {
        printf("No student records available.\n");
        return;
    }

    // Bubble sort by Name
    for (int i = 0; i < student_count - 1; i++) 
    {
        for (int j = 0; j < student_count - i - 1; j++) 
        {
            if (strcmp(students[j].name, students[j + 1].name) > 0) 
            {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("Students sorted by Name:\n");
    display_student_detiails();
}