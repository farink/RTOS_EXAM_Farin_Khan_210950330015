/*2. Create 3 realtime tasks each with the periodcity 
T1=1000ms, T2=2000ms, T3=5000ms. 
Also create use oneshot software timer to trigger a 
callback function from T3 after 10000ms.*/



#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include<stdio.h>
#include<freertos/timers.h>

    BaseType_t Task1;
    BaseType_t Task2;
    BaseType_t Task3;
    TaskHandle_t taskhandle1;
    TaskHandle_t taskhandle2;
    TaskHandle_t taskhandle3;

    TimerHandle_t One_Shot;

void T1_task(void *pvParameters)
{
    while (1)
    {
        printf("TASK 1\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void T2_task(void *pvParameters)
{
    while (1)
    {
        printf("TASK 2\n");
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void T3_task(void *pvParameters)
{
    while (1)
    {
        printf("TASK 3\n");

        void OneShotCallback( TimerHandle_t xTimer )
        {
        printf("Function is expired and One Shot Timer is called\n");
        }
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
void OneShotCallback( TimerHandle_t xTimer )
{
printf("Function is expired and One Shot is called\n");
}

void app_main()
{
    Task1 = xTaskCreate(T1_task, "Task 1 ", 2048, NULL, 5, &taskhandle1);
    if(Task1 = pdPASS)
    {
        printf("Task 1 is created\n");
    }

    Task2 = xTaskCreate(T2_task, "Tasks 2 ", 2048, NULL, 6, &taskhandle2);
    if(Task2 = pdPASS)
    {
        printf("Task 2 is created\n"); 
    }

    Task3 = xTaskCreate(T3_task, "Tasks 3 ", 2048, NULL, 7, &taskhandle3);
    if(Task3 = pdPASS)
    {
         printf("Task 3 is created\n");
    }
    
    One_Shot = xTimerCreate("Autoreload", pdMS_TO_TICKS(10000), pdFALSE, NULL, OneShotCallback );
    xTimerStart(One_Shot, 0);

    
}