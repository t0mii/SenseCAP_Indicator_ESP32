#ifndef INDICATOR_MARIADB_H
#define INDICATOR_MARIADB_H

#include <stdbool.h>
#include <stdint.h>
#include "view_data.h"

#ifdef __cplusplus
extern "C" {
#endif

/* MariaDB configuration structure */
struct mariadb_config {
    bool enabled;
    char host[64];
    uint16_t port;
    char user[32];
    char password[64];
    char database[32];
    char table[32];
    uint16_t interval_minutes;  /* Export interval in minutes */
};

/* Initialize the MariaDB module */
int indicator_mariadb_init(void);

/* Get current MariaDB configuration */
int indicator_mariadb_get_config(struct mariadb_config *config);

/* Set and save MariaDB configuration */
int indicator_mariadb_set_config(const struct mariadb_config *config);

/* Test the database connection */
int indicator_mariadb_test_connection(void);

/* Manually trigger a data export */
int indicator_mariadb_export_now(void);

/* Get last export status (0 = success, negative = error code) */
int indicator_mariadb_get_last_status(void);

/* Get timestamp of last successful export */
time_t indicator_mariadb_get_last_export_time(void);

#ifdef __cplusplus
}
#endif

#endif /* INDICATOR_MARIADB_H */
