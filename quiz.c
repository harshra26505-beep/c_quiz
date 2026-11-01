#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_QUESTIONS 50

typedef struct {
    char question[256];
    char options[4][100];
    char correct_option;
} Question;

// Helper function to remove the newline character left by fgets()
void strip_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

int main() {
    printf("==================================================\n");
    printf("              C-MASTERY QUIZ ENGINE               \n");
    printf("==================================================\n");
    printf("          Developed by: HARSH RAJ & ASHVI          \n");
    printf("          Version 1.0 | 2026 Edition              \n");
    printf("--------------------------------------------------\n\n");
    FILE *file = fopen("quiz.txt", "r");
    
    // Safety check: ensure the file exists and can be opened
    if (file == NULL) {
        printf("Error: Could not open quiz.txt. Make sure the file exists.\n");
        return 1; 
    }

    Question quiz[MAX_QUESTIONS];
    int num_questions = 0;
    char buffer[256];

    // Read the file line by line
    while (num_questions < MAX_QUESTIONS && fgets(buffer, sizeof(buffer), file)) {
        
        // 1. Read Question
        strip_newline(buffer);
        strncpy(quiz[num_questions].question,buffer,
        sizeof(quiz[num_questions].question)-1);

        // 2. Read the 4 Options
      for (int i = 0; i < 4; i++) {
    if (!fgets(buffer, sizeof(buffer), file)) {
        printf("Error reading question data.\n");
        fclose(file);
        return 1;
    }

    strip_newline(buffer);
    strncpy(quiz[num_questions].options[i],buffer,
sizeof(quiz[num_questions].options[i])-1);
}

        // 3. Read Correct Answer
        if (fgets(buffer, sizeof(buffer), file)) {
           char ans = toupper(buffer[0]);
if(ans >= 'A' && ans <= 'D')
quiz[num_questions].correct_option = ans;
else {
printf("Invalid answer key in file\n");
return 1;
}
        }

        num_questions++;
    }

    fclose(file);

    if (num_questions == 0) {
        printf("No questions found in the file.\n");
        return 1;
    }

    int score = 0;
    char answer;

    printf("=== Welcome to the C Programming Quiz ===\n");
    printf("Successfully loaded %d questions.\n", num_questions);

    // Run the quiz using the loaded data
    for (int i = 0; i < num_questions; i++) {
        printf("\nQuestion %d: %s\n", i + 1, quiz[i].question);
        
        for (int j = 0; j < 4; j++) {
            printf("%s\n", quiz[i].options[j]);
        }

        printf("Enter your answer (A, B, C, or D): ");
        scanf(" %c", &answer); 
        answer = toupper(answer);


        if (answer == quiz[i].correct_option) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Wrong! The correct answer was %c.\n", quiz[i].correct_option);
        }
    }
    printf("==================================================\n");
    printf("                  QUIZ COMPLETE!                  \n");
    printf("==================================================\n\n");
    printf("Your final score is: %d out of %d\n", score, num_questions);
    float percentage=((float)score / num_questions)*100;
    printf("Percentage: %.2f%%\n",percentage);
   
    if (percentage >= 80.0) {
        printf("Outstanding performance!\n");
    } else if (percentage >= 50.0) {
        printf("Good job, but room for improvement!\n");
    } else {
        printf("You might need to study a bit more.\n");
    }

    return 0;
}