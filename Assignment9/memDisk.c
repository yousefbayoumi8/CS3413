#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef int bool;
#define true 1
#define false 0

typedef struct request{
    int sector;
    unsigned int arrival;
    struct request *next;
};

int head;
double time;
int requestInQueue;
char * algorithm;
bool directionFroward = true;

struct request * front;

void printReq(struct request * req);
void printReqList();
void init(char * arr[]);
void enqueue(int s, unsigned int t);
void dequeueReq(struct request * req);
double fcfs();
double sstf();
double cscan();
double look();
void service();

void printReq(struct request * req){
    printf("Request: sector: %d, arrival: %u\n", req->sector, req->arrival);
}

void printReqList(){
    struct request * temp = front;
    printf("\tLIST<\n");
    while(temp != NULL){
        printReq(temp);
        temp = temp->next;
    }
    printf("\t>LIST\n");
}

void init(char * arr[]){
    time = 0;
    requestInQueue = 0;
    head = atoi(arr[2]);
    if(arr[1][0] == 'F'){
        algorithm = "First Come First Serve";
    }
    else if (arr[1][0] == 'T'){
        algorithm = "Shortest Seek Time First";
    }
    else if(arr[1][0] == 'C'){
        algorithm = "Circular SCAN";
    }
    else if(arr[1][0] == 'L'){
        algorithm = "LOOK";
    }
    else{
        algorithm = "UNDEFINED";
    }
}

void enqueue(int s, unsigned int t){
    struct request * temp = (struct request *) malloc(sizeof(struct request));
    temp->sector = s;
    temp->arrival = t;
    struct request * tmp = front;
    if(tmp == NULL){
        front = temp;
        requestInQueue++;
    }
    else{
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = temp;
        requestInQueue++;
    }
}

void dequeueReq(struct request * req){
    struct request * tmp = front;
    struct request * tmpNext = front;
    if(front == req){
        front = front->next;
        requestInQueue--;
        return;
    }
    if(tmp != NULL){
        tmpNext = tmp->next;
    }
    else{
        tmp = NULL;
        return;
    }
    while(tmpNext != req && tmpNext != NULL){
        tmp = tmpNext;
        tmpNext = tmpNext->next;
    }
    tmp->next = tmpNext->next;
    requestInQueue--;
}

double timeAdjust(int dest){
    int dist = abs(dest) - head;
    double t = ((double)abs(dist)/(double)10);
    if(dist < 0 && directionFroward){
        t += 5;
    }
    else if(dist >= 0 && !directionFroward){
        t += 5;
    }
    printf("\tt: %f\n", t);
    return t;
}

double fcfs(){
    double t = timeAdjust(-1);
    printf("HEY\n");
    return t;
}

void service(){
    printf("\nHEY\n");
    double t;
    if(algorithm[0] == 'F'){
        t = fcfs();
    }
    else if(algorithm[0] == 'S'){
        t = fcfs();
    }
    time += t;
    head = front->sector;
}

int main(int argc, char ** argv){
    printf("main\n");
    if(argc > 4 || argc < 3){
        printf("Usage: ./memDisk (one of: F T C L)\n");
        return EXIT_FAILURE;
    }
    init(argv);
    if(algorithm == "UNDEFINED"){
        printf("Usage: ./memDisk (one of: F T C L)\n");
        return EXIT_FAILURE;
    }
    bool timePass = true;
    int sectorIn, i;
    unsigned int timeIn;
    printf("head: %d, algorithm: %s\n", head, algorithm);
    i = scanf("%d %u", &sectorIn, &timeIn);
    if(i != 2){
        timePass = false;
    }
    while(timePass){
        printf("Time: %f\n", time);
        if(i == 2){ // read something to enqueue
            printf("sectorIn: %d, timeIn: %u\n", sectorIn, timeIn);
            enqueue(sectorIn, timeIn);
            i = scanf("%d %u", &sectorIn, &timeIn);
        }
        if(front != NULL){
            service();
        }
        if ((i != 2 && front == NULL) || time > 70){ // nothing read in
            timePass = false;
        }
        time += 1;
    }
    printReqList();
    dequeueReq(front);
    printReqList();
    dequeueReq(front);
    printReqList();
    dequeueReq(front->next->next);
    printReqList();
}