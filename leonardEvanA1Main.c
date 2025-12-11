#include "givenA1.h"
#include "helper.h"

int main (int argc, char * argv[]) {

    // Variables For Main Menu
    int choice;
    int isFileRead = 0;

    // Variables For Task 1
    char fName [30]; 
    struct Animal dataZoo [NUM_SAMPLES];

    // Variables For Task 2
    int vector1 [NUM_FEATURES] = {1,1,1,0,1,0,1,1,1,0,0,0,0,1,1,1}; 
    int vector2 [NUM_FEATURES] = {1,0,0,1,0,0,1,1,1,1,0,0,4,0,0,1};
    float enclideanDistance; 
    float jaccardSimilarity;
    int hammingDistance;

    // Variables For Task 3
    int newSample [NUM_FEATURES] = {1,1,1,0,1,0,1,1,1,0,0,0,0,1,1,1};
    int k, whichDistanceFunction;
    int kNearestNeighbors [NUM_SAMPLES];

    // Variables For Task 4
    int predictedClass;

    // Variables For Task 5
    int isTestFileRead;
    char testFName [30];
    struct Animal testDataZoo [NUM_TEST_DATA];
    float accuracy;

    do{
        do{
            // Prints The Main Menu
            printf ("\nHere is the menu - enter a number between 1 and 6 \n\n");
            printf ("1.    Read Data From A File\n");
            printf ("2.    Calculate The Euclidean Distance, Hamming Distance, and Jaccard Similarity Of Two Vectors \n");
            printf ("3.    Find The Nearest Neighboors When Compaired To Another Set Of Data\n");
            printf ("4.    Predict The Class Of Another Set Of Data Based On The Nearest Neighboors\n");
            printf ("5.    Calculate The Accuracy Of The Class Prediction Of Another Set Of Data\n");
            printf ("6.    Exit \n");
        
            // Prompts User To Enter Their Choice
            printf ("Enter your choice: ");
            scanf ("%d", &choice);
            printf("\n");

            // Makes Sure User Enters A Valid Choice 
            if(choice < 1 || choice > 6){
                printf("Invalid choice. Enter a number between 1 and 6\n");
            }
        }while(choice < 1 || choice > 6);

        // Ensures The File Is Read Before Any Other Option
        while(choice != 1 && choice != 2 && choice != 6 && isFileRead != 1){
                printf("The file must be read before performing any operations on its data\n");
                printf ("Enter your choice: ");
                scanf ("%d", &choice);
                printf("\n");
        }

        switch (choice) {
            case 1:
                // Prompts User To Enter The Name Of The File
                printf ("Enter the name of the file: ");
                scanf ("%s", fName);

                // Reads The File
                isFileRead = readFromFile(fName, dataZoo);

                // Validates If The File Was Read
                if(isFileRead == 1){
                    printf("File Read Successfully\n");
                } 
                else {
                    printf("File Read Unsuccessfully\n");
                }
              
                break;

            case 2:
                // Calls The Distance Functions
                distanceFunctions(vector1, vector2, &enclideanDistance, &hammingDistance, &jaccardSimilarity);

                // Prints The Results
                printf("Euclidean Distance: %f\n", enclideanDistance);
                printf("Hamming Distance: %d\n", hammingDistance);
                printf("Jaccard Similarity: %f\n", jaccardSimilarity);
                
                break;
            
            case 3:
                do{
                    // Prompts User To Enter The Amount Of Nearest Neighboors The Want To Find
                    printf("Enter the number of nearest neighbors to find: ");
                    scanf("%d", &k);
                    printf("\n");

                    // Validates That The Users Choice Is Within The Range Of Samples
                    if(k < 1 || k > NUM_SAMPLES){
                        printf("%d Is not a valid choice, please enter a number between 1 and %d\n", k, NUM_SAMPLES);
                    }

                } while(k < 1 || k > NUM_SAMPLES);

                do{
                    // Prompts User To Enter The Distance Function They Want To Use
                    printf("Would you like to: \n");
                    printf("1.  Find Euclidean Distance\n");
                    printf("2.  Find Hamming Distance\n");
                    printf("3.  Find Jaccard Similarity\n");
                    printf("Enter your choice: ");
                    scanf("%d", &whichDistanceFunction);

                    // Validates The Users Choice
                    if(whichDistanceFunction < 1 || whichDistanceFunction > 3){
                        printf("%d Is not a valid choice, please enter either 1, 2, 3\n", whichDistanceFunction);
                    }

                    printf("\n");

                }while(whichDistanceFunction < 1 || whichDistanceFunction > 3);

                // Calls The Find K Nearest Neighboors Function
                findKNearestNeighbors(dataZoo, newSample, k, whichDistanceFunction, kNearestNeighbors);

                // Prints The Results If User Wants The k Closest Euclidean Distance
                if(whichDistanceFunction == 1){
                    printf("%d Nearest neighbors for the new sample with Euclidean Distance: ", k);

                    for(int i = 0; i < k; i++){
                        printf("%d ", kNearestNeighbors[i]);
                    } 
                }

                // Prints The Results If User Wants The k Closest Hamming Distance
                else if(whichDistanceFunction == 2){
                    printf("%d Nearest neighbors for the new sample with Hamming Distance: ", k);

                    for(int i = 0; i < k; i++){
                        printf("%d ", kNearestNeighbors[i]);
                    }
                }

                // Prints The Results If User Wants The k Closest Jaccard Similarity
                else if(whichDistanceFunction == 3){
                    printf("%d Nearest neighbors for the new sample with Jaccard Similarity: ", k);

                    for(int i = 0; i < k; i++){
                        printf("%d ", kNearestNeighbors[i]);
                    }
                    
                }

                printf("\n");

                break;

            case 4:
                do{
                    // Prompts User To Enter The Amount Of Nearest Neighboors The Want To Find
                    printf("Enter the number of nearest neighbors to find: ");
                    scanf("%d", &k);
                    printf("\n");

                    // Validates That The Users Choice Is Within The Range Of Samples
                    if(k < 1 || k > NUM_SAMPLES){
                        printf("%d Is not a valid choice, please enter a number between 1 and %d\n", k, NUM_SAMPLES);
                    }

                } while(k < 1 || k > NUM_SAMPLES);

                do{
                    // Prompts User To Enter The Distance Function They Want To Use
                    printf("Would you like to predict class based on: \n");
                    printf("1.  Euclidean Distance\n");
                    printf("2.  Hamming Distance\n");
                    printf("3.  Jaccard Similarity\n");
                    printf("Enter your choice: ");
                    scanf("%d", &whichDistanceFunction);

                    // Validates The Users Choice
                    if(whichDistanceFunction < 1 || whichDistanceFunction > 3){
                        printf("%d Is not a valid choice, please enter either 1, 2, 3\n", whichDistanceFunction);
                    }

                    printf("\n");

                }while(whichDistanceFunction < 1 || whichDistanceFunction > 3);

                // Calls The Predict Class Function
                predictedClass = predictClass(dataZoo, newSample, whichDistanceFunction, k);

                // Prints The Results
                printf("The predicted class for the new sample is: %d\n", predictedClass);

                break;

            case 5:

                if(isTestFileRead != 1){
                    // Prompts User To Enter The Name Of The File
                    printf ("Enter the name of the test file: ");
                    scanf ("%s", testFName);

                    // Reads The File
                    isTestFileRead = readFromTestFile(testFName, testDataZoo);

                    // Validates If The File Was Read
                    if(isTestFileRead == 1){
                        printf("File Read Successfully\n");
                    } 
                    else{
                        printf("File Read Unsuccessfully\n");
                    }
                }   

                do{
                    // Prompts User To Enter The Amount Of Nearest Neighboors The Want To Find
                    printf("Enter the number of nearest neighbors to find: ");
                    scanf("%d", &k);
                    printf("\n");

                    // Validates That The Users Choice Is Within The Range Of Samples
                    if(k < 1 || k > NUM_SAMPLES){
                        printf("%d Is not a valid choice, please enter a number between 1 and %d\n", k, NUM_SAMPLES);
                    }

                } while(k < 1 || k > NUM_SAMPLES);

                do{
                    // Prompts User To Enter The Distance Function They Want To Use
                    printf("Would you like to predict class based on: \n");
                    printf("1.  Euclidean Distance\n");
                    printf("2.  Hamming Distance\n");
                    printf("3.  Jaccard Similarity\n");
                    printf("Enter your choice: ");
                    scanf("%d", &whichDistanceFunction);

                    // Validates The Users Choice
                    if(whichDistanceFunction < 1 || whichDistanceFunction > 3){
                        printf("%d Is not a valid choice, please enter either 1, 2, 3\n", whichDistanceFunction);
                    }

                    printf("\n");

                }while(whichDistanceFunction < 1 || whichDistanceFunction > 3);

                // Calls The Find Accuracy Function 
                accuracy = findAccuracy(dataZoo, whichDistanceFunction, testDataZoo, k);

                // Prints The Results
                printf("The accuracy for the test data is: %f\n", accuracy);

                break;
            
            case 6: printf ("Goodbye\n");
                break;
        }
        
    } while (choice != 6);

    return 0;
}