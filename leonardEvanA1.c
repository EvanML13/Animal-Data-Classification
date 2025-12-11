#include "givenA1.h"
#include "helper.h"

// TASK 1 - Function To Read From File
int readFromFile (char fName[30], struct Animal dataZoo[NUM_SAMPLES]){

    int count = 0;
    FILE * fptr;

    // Opens The File 
    fptr = fopen(fName, "r");

    // Returns -1 For An Abnormal Exit
    if(fptr == NULL){
        return -1;
    }

    // Fills The Struct With Data From The File 
    while(count < NUM_SAMPLES && fscanf(fptr, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", dataZoo[count].animalName, &dataZoo[count].features[0], &dataZoo[count].features[1], &dataZoo[count].features[2], &dataZoo[count].features[3], &dataZoo[count].features[4], &dataZoo[count].features[5], &dataZoo[count].features[6], &dataZoo[count].features[7], &dataZoo[count].features[8], &dataZoo[count].features[9], &dataZoo[count].features[10], &dataZoo[count].features[11], &dataZoo[count].features[12], &dataZoo[count].features[13], &dataZoo[count].features[14], &dataZoo[count].features[15], &dataZoo[count].classLabel) == 18){
        
        // Prints The Data That Is Being Read
        printf("%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", dataZoo[count].animalName, dataZoo[count].features[0], dataZoo[count].features[1], dataZoo[count].features[2], dataZoo[count].features[3], dataZoo[count].features[4], dataZoo[count].features[5], dataZoo[count].features[6], dataZoo[count].features[7], dataZoo[count].features[8], dataZoo[count].features[9], dataZoo[count].features[10], dataZoo[count].features[11], dataZoo[count].features[12], dataZoo[count].features[13], dataZoo[count].features[14], dataZoo[count].features[15], dataZoo[count].classLabel);
        
        count++;
    }

    // Closes File
    fclose(fptr);

    return 1;
}

// TASK 2 - Function To Calculate The Euclidean Distance, Hamming Distance, and Jaccard Similarity Of Two Vectors
void distanceFunctions (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES], float * euclideanDistance, int * hammingDistance, float * jaccardSimilarity){
    
    // Declare Variables
    int sum = 0, oneToOne = 0, zeroToZero = 0;
    *hammingDistance = 0;

    // Iterates Through Each Element Of Both Vectors
    for(int i = 0; i < NUM_FEATURES; i++){

        // Calculates The Sum
        sum += (vector1[i] - vector2[i]) * (vector1[i] - vector2[i]);

        // Checks If The Two Elements Are Not Equal, Then Increases The Hamming Distance 
        if(vector1[i] != vector2[i]){
            (*hammingDistance)++;
        }

        // Checks If The Two Elements Are Both One, Then Increases The One To One Counter
        if(vector1[i] == 1 && vector2[i] == 1){
            oneToOne++;
        }

        // Checks If The Two Elements Are Both Zero, Then Increases The Zero To Zero Counter
        if(vector1[i] == 0 && vector2[i] == 0){
            zeroToZero++;
        }
    }

    // Calculates The Divisor For The Jaccard Similarity
    zeroToZero = NUM_FEATURES - zeroToZero;

    // Calculates The Euclidean Distance
    *euclideanDistance = sqrt(sum);

    // Calculates The Jaccard Similarity
    if (zeroToZero != 0){
        *jaccardSimilarity = (float) oneToOne / zeroToZero;
    }

    // If The Divisor Is Zero, Then The Jaccard Similarity Is Zero
    else{
        *jaccardSimilarity = 0.0;
    }
}


// TASK 3 - Function To Find The Nearst Neighboors When Compaired To Another Set Of Data 
void findKNearestNeighbors (struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES], int k, int whichDistanceFunction, int kNearestNeighbors [NUM_SAMPLES]){

    // Declare Variables
    float distance[NUM_SAMPLES];
    int indices[NUM_SAMPLES];
    float enclideanDistance; 
    float jaccardSimilarity;
    int hammingDistance;
    float temp = 0;
    int tempIndex = 0;

    int dataSample[NUM_FEATURES];

    // Iterates Through Each Sample And Enters Them Into The Distance Function
    for(int i = 0; i < NUM_SAMPLES; i++){

        for(int j = 0; j < NUM_FEATURES; j++){
            dataSample[j] = dataZoo[i].features[j];
        }

        // Calls The Distance Function To Calculate Between The Two Vectors
        distanceFunctions(newSample, dataSample, &enclideanDistance, &hammingDistance, &jaccardSimilarity);

        // Checks Which Distance Function To Use
        if(whichDistanceFunction == 1){
            distance[i] = enclideanDistance;
        }
        else if(whichDistanceFunction == 2){
            distance[i] = hammingDistance;   
        }
        else{
            distance[i] = jaccardSimilarity; 
        }

        // Stores Indices
        indices[i] = i;
    }

    // Used Bubble Sort Methiod To Correctly Order The Arrays, Learned From https://www.programiz.com/dsa/bubble-sort 

    // Compaires Two Distances
    for(int i = 0; i < NUM_SAMPLES - 1; i++){
        for(int j = i + 1; j < NUM_SAMPLES; j++){

            // If User Wants To Calculate The Euclidean Distance or Hamming Distance And The Values Are In The Wrong Order  
            if((whichDistanceFunction == 1 || whichDistanceFunction == 2) && distance[i] > distance[j]){

                // Swaps The Distance Values
                temp = distance[i];
                distance[i] = distance[j];
                distance[j] = temp;

                // Swaps The Indices
                tempIndex = indices[i];
                indices[i] = indices[j];
                indices[j] = tempIndex;
            }

            // If User Wants To Calculate The Jaccard Similarity And The Values Are In The Wrong Order
            else if(whichDistanceFunction == 3 && distance[i] < distance[j]){
                
                // Swaps The Distance Values
                temp = distance[i];
                distance[i] = distance[j];
                distance[j] = temp;

                // Swaps The Indices
                tempIndex = indices[i];
                indices[i] = indices[j];
                indices[j] = tempIndex;
            }
        }
    }

    // Stores The K Nearest Neighboors In The Array
    for(int i = 0; i < k; i++){
        kNearestNeighbors[i] = indices[i];
    }
}

// TASK 4 - Function To Predict The Class Of A New Sample
int predictClass (struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES], int whichDistanceFunction, int k){

    // Declare Variables
    int kNearestNeighbors[k];
    int classCount[NUM_CLASSES + 1] = {0};
    int predictedClass = -1;
    int classLabel;
    int maxCount = 0;

    // Calls Task 3 To Find The Nearest Neighboors
    findKNearestNeighbors(dataZoo, newSample, k, whichDistanceFunction, kNearestNeighbors);

    // Iterates Through k Nearest Neighboors
    for(int i = 0; i < k; i++){

        // Gets The Class Label For The Current Nearest Neighboor
        classLabel = dataZoo[kNearestNeighbors[i]].classLabel;

        if(classLabel >= 0 && classLabel <= NUM_CLASSES){

            // Increases The Count For The Class Label
            classCount[classLabel]++;
        }
    }

    // Iterates Through Each Class
    for(int i = 0; i <= NUM_CLASSES; i++){

        // Is Current Class Occurs More Frequent Than The Previous Most Frequent Class
        if(classCount[i] > maxCount){
            
            // Updates The Most Frequent Class
            maxCount = classCount[i];
            
            // Updates The Amount Of Classes Predicted
            predictedClass = i;
        }
    }

    // Returns The Predicted Class
    return predictedClass; 
}

// TASK 5 - Function To Calculate The Accuracy Of The Class Prediction Of Another Set Of Data
float findAccuracy (struct Animal dataZoo [NUM_SAMPLES], int whichDistanceFunction, struct Animal testData [NUM_TEST_DATA], int k){

    // Declare Variables
    int correctPredictions = 0;
    int predictedClass;
    float accuracy;

    for(int i = 0; i < NUM_TEST_DATA; i++){

        // Calls Task 4 To Predict The Class
        predictedClass = predictClass(dataZoo, testData[i].features, whichDistanceFunction, k);
        printf("%d ", predictedClass);

        // Checks If The Predicted Class Is Correct
        if(predictedClass == testData[i].classLabel){
            correctPredictions++;
        }
    }
    
    printf("\n");
    printf("%d\n", correctPredictions);
    printf("%d\n", NUM_TEST_DATA);

    // Calculates The Accuracy
    accuracy = (float) correctPredictions / (float) NUM_TEST_DATA;

    return accuracy;
}

// Helper Function To Have The Same Function As Task 1 But For The Test Data In Task 5
int readFromTestFile (char testFName [30], struct Animal testDataZoo [NUM_TEST_DATA]){
    
    int count = 0;
    FILE * fptr;

    // Opens The File 
    fptr = fopen(testFName, "r");

    // Returns -1 For An Abnormal Exit
    if(fptr == NULL){
        return -1;
    }

    // Fills The Struct With Data From The File 
    while(count < NUM_TEST_DATA && fscanf(fptr, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", testDataZoo[count].animalName, &testDataZoo[count].features[0], &testDataZoo[count].features[1], &testDataZoo[count].features[2], &testDataZoo[count].features[3], &testDataZoo[count].features[4], &testDataZoo[count].features[5], &testDataZoo[count].features[6], &testDataZoo[count].features[7], &testDataZoo[count].features[8], &testDataZoo[count].features[9], &testDataZoo[count].features[10], &testDataZoo[count].features[11], &testDataZoo[count].features[12], &testDataZoo[count].features[13], &testDataZoo[count].features[14], &testDataZoo[count].features[15], &testDataZoo[count].classLabel) == 18){

        count++;
    }

    // Closes File
    fclose(fptr);

    return 1;

}