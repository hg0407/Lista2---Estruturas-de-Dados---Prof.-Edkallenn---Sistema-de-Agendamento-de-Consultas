#include <stdio.h>
#include <stdlib.h>

/*
** Função : Sistema de Agendamento de Consultas
** Autor : Hygor Alves
** Data : 04/06/2024
** Observações: Este programa permite agendar consultas com médico e enfermagem em uma clínica médica.
*/

#define MAX_MEDICAL_APPOINTMENTS 5

typedef struct {
    int front, rear;
    int appointments[MAX_MEDICAL_APPOINTMENTS];
} MedicalAppointmentQueue;

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} NurseAppointmentQueue;

void initMedicalQueue(MedicalAppointmentQueue *queue) {
    queue->front = queue->rear = -1;
}

int isMedicalQueueFull(MedicalAppointmentQueue *queue) {
    return queue->rear == MAX_MEDICAL_APPOINTMENTS - 1;
}

int isMedicalQueueEmpty(MedicalAppointmentQueue *queue) {
    return queue->front == -1;
}

void enqueueMedicalAppointment(MedicalAppointmentQueue *queue, int patient) {
    if (isMedicalQueueFull(queue)) {
        printf("Não é possível agendar mais consultas com médico.\n");
        return;
    }

    if (queue->front == -1) {
        queue->front = 0;
    }

    queue->rear++;
    queue->appointments[queue->rear] = patient;
}

int dequeueMedicalAppointment(MedicalAppointmentQueue *queue) {
    if (isMedicalQueueEmpty(queue)) {
        printf("Não há consultas com médico agendadas.\n");
        return -1;
    }

    int patient = queue->appointments[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }

    return patient;
}

// Funções para manipular a fila dinâmica de agendamento com enfermagem
void initNurseQueue(NurseAppointmentQueue *queue) {
    queue->front = queue->rear = NULL;
}

int isNurseQueueEmpty(NurseAppointmentQueue *queue) {
    return queue->front == NULL;
}

void enqueueNurseAppointment(NurseAppointmentQueue *queue, int patient) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = patient;
    newNode->next = NULL;

    if (isNurseQueueEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

int dequeueNurseAppointment(NurseAppointmentQueue *queue) {
    if (isNurseQueueEmpty(queue)) {
        printf("Não há consultas com enfermagem agendadas.\n");
        return -1;
    }

    Node* temp = queue->front;
    int patient = temp->data;
    queue->front = queue->front->next;
    free(temp);

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    return patient;
}

int main() {
    
    MedicalAppointmentQueue medicalQueue;
    NurseAppointmentQueue nurseQueue;

    initMedicalQueue(&medicalQueue);
    initNurseQueue(&nurseQueue);

    enqueueMedicalAppointment(&medicalQueue, 1);
    enqueueMedicalAppointment(&medicalQueue, 2);
    enqueueMedicalAppointment(&medicalQueue, 3);
    enqueueMedicalAppointment(&medicalQueue, 4);
    enqueueMedicalAppointment(&medicalQueue, 5);

    enqueueNurseAppointment(&nurseQueue, 6);
    enqueueNurseAppointment(&nurseQueue, 7);

    printf("Consulta com médico agendada para o paciente %d.\n", dequeueMedicalAppointment(&medicalQueue));
    printf("Consulta com médico agendada para o paciente %d.\n", dequeueMedicalAppointment(&medicalQueue));
    printf("Consulta com enfermagem agendada para o paciente %d.\n", dequeueNurseAppointment(&nurseQueue));
    printf("Consulta com enfermagem agendada para o paciente %d.\n", dequeueNurseAppointment(&nurseQueue));

    return 0;
}
