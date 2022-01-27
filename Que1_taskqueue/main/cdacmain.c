/*1. Create 3 realtime tasks each with the periodcity 
T1=1000ms, T2=2000ms, T3=5000ms. 
Also create two additional task T4 and T5 where T4 
sends integer data to T5 using Messsage Queues.*/

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <freertos/queue.h>


TaskHandle_t Handle1;
TaskHandle_t Handle2;
TaskHandle_t Handle3;
TaskHandle_t Handle4;
TaskHandle_t Handle5;
//BaseType_t Qsend;
QueueHandle_t queue;

void Task1(void *pvParameters)
{
    while (1)
    {
        printf("Task 1\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void Task2(void *pvParameters)
{
    while (1)
    {
        printf("Task 2\n");
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void Task3(void *pvParameters)
{
    while (1)
    {
        printf("Task 3\n");
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void Task4_send(void *pvparameters)
{
    int sending_data=0;
    while(1)
    {
        sending_data++;
        printf("Task4  RUNNING:%d\n",sending_data);
        xQueueSend(queue,&sending_data,portMAX_DELAY);
        vTaskDelay(100/ portTICK_PERIOD_MS);
    }
}
void Task5_receive(void *pvparameters)
{
    while(1)
    {
         int rece_data=0;
        xQueueReceive(queue,&rece_data,portMAX_DELAY);
        printf("RECEIVED DATA :%d\n",rece_data);
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
}

void app_main()
{
    queue=xQueueCreate(4,sizeof(int));
    BaseType_t Task1;
    BaseType_t Task2;
    BaseType_t Task3;
    BaseType_t Task4;
    BaseType_t Task5;

    Task1=xTaskCreate(Task1, "Task1",2048,NULL,5,&Handle1);
    if(Task1==pdPASS)
    {
        printf("Task1 created\n");
    }
    Task2=xTaskCreate(Task2,"Task2",2048,NULL,6,&Handle2);
    if(task2==pdPASS)
    {
        printf("Task2 created\n");
    }
    Task3=xTaskCreate(Task3,"Task3",2048,NULL,7,&Handle3);
    if(Task3==pdPASS)
    {
        printf("Task3 created\n");
    }
    Task4=xTaskCreate(Task4_send, "Task4",2048,NULL,8,&Handle4);
    if(Task4==pdPASS)
    {
        printf("Task4 created\n");
    }
    Task5=xTaskCreate(Task5_receive, "Task5",2048,NULL,9,&Handle5);
    if(Task5==pdPASS)
    {
        printf("Task5 created\n");
    }
}
