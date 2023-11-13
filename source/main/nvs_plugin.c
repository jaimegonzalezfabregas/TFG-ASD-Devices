#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "./nvs_plugin.h"
#include "nvs.h"
int inited = 0;
#define STORAGE_NAMESPACE "storage"

void init_nvs()
{
    if (inited)
        return;
    // Initialize NVS
    esp_err_t err = nvs_flash_init();

    ESP_ERROR_CHECK(err);
    inited = 1;
}

void j_nvs_set(char *key, void *buffer, int buffer_size)
{
    init_nvs();

    nvs_handle_t my_handle;
    ESP_ERROR_CHECK(nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &my_handle));
    ESP_ERROR_CHECK(nvs_set_blob(my_handle, key, buffer, buffer_size));
    ESP_ERROR_CHECK(nvs_commit(my_handle));
    nvs_close(my_handle);
    char *test[100];
    ESP_LOGE("NVS", "nvs set of %s", key);
    j_nvs_get(key, test, 100);
}
int j_nvs_get(char *key, void *buffer, int buffer_size)
{
    init_nvs();

    nvs_handle_t my_handle;
    ESP_ERROR_CHECK(nvs_open(STORAGE_NAMESPACE, NVS_READONLY, &my_handle));
    size_t len = (size_t)buffer_size;
    int err = nvs_get_blob(my_handle, key, buffer, &len);
    ESP_LOGE("NVS", "nvs get of %s got err:%s", key, esp_err_to_name(err));
    nvs_close(my_handle);

    return err;
}