#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "../common.h"
#include "esp_camera.h"

enum OTACommand
{
    Update,
    CancelRollback
};

char *ota_command_to_string[] = {
    "Update",
    "CancelRollback",
};

struct OTAMsg
{
    enum OTACommand command;
    char url[OTA_URL_SIZE];
};

struct OTAConf
{
    QueueHandle_t to_mqtt_queue;
    QueueHandle_t to_ota_queue;
    QueueHandle_t to_screen_queue;
    // camera_config_t *cam_conf;
};

void ota_start(struct OTAConf *conf);