/* An hwmon driver for Cameo ESCC601-32Q Innovium i2c Module */
#pragma GCC diagnostic ignored "-Wformat-zero-length"
#include "x86-64-cameo-escc601-32q.h"
#include "x86-64-cameo-escc601-32q-common.h"
#include "x86-64-cameo-escc601-32q-sys.h"

/* extern i2c_client */
extern struct i2c_client *Cameo_CPLD_30_client; //0x30 for SYS CPLD
extern struct i2c_client *Cameo_CPLD_31_client; //0x31 for Port 01-16
extern struct i2c_client *Cameo_CPLD_32_client; //0x32 for Port 17-32
extern struct i2c_client *Cameo_CPLD_23_client; //0x23 for Fan CPLD
extern struct i2c_client *Cameo_BMC_14_client;  //0x14 for BMC slave
/* end of extern i2c_client */

/* implement i2c_function */
ssize_t cpld_hw_ver_get(struct device *dev, struct device_attribute *da, char *buf)
{
    int status = -EPERM;
    struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct Cameo_i2c_data *data = i2c_get_clientdata(Cameo_CPLD_30_client);
    
    mutex_lock(&data->update_lock);
    sprintf(buf, "");
    switch (attr->index)
    {
        case 23:
            if( bmc_enable() == ENABLE)
            {
                status = i2c_smbus_read_byte_data(Cameo_BMC_14_client, 0xff);
            }
            else
            {
                status = i2c_smbus_read_byte_data(Cameo_CPLD_23_client, CPLD_VER_REG);
            }
        case 30:
            status = i2c_smbus_read_byte_data(Cameo_CPLD_30_client, CPLD_VER_REG);
        case 31:
            status = i2c_smbus_read_byte_data(Cameo_CPLD_31_client, CPLD_VER_REG);
        case 32:
            status = i2c_smbus_read_byte_data(Cameo_CPLD_32_client, CPLD_VER_REG);
    }
    if(status < 0)
    {
        mutex_unlock(&data->update_lock);
        return status;
    }
    else
    {
        mutex_unlock(&data->update_lock);
        sprintf(buf, "%s0x%x\n", buf, status);
    }
    return sprintf(buf, "%s\n", buf);
}

ssize_t wdt_enable_get(struct device *dev, struct device_attribute *da, char *buf)
{
    struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct Cameo_i2c_data *data = i2c_get_clientdata(Cameo_CPLD_30_client);
    
    mutex_lock(&data->update_lock);
    sprintf(buf, "");
    if (attr->index == EEPROM_WP)
    {
        if (i2c_smbus_read_byte_data(Cameo_CPLD_30_client, WDT_EN_REG) & BIT_4_MASK)
        {
            sprintf(buf, "%s%d\n", buf, ENABLE);
        }
        else
        {
            sprintf(buf, "%s%d\n", buf, DISABLE);
        }
    }
    mutex_unlock(&data->update_lock);
    return sprintf(buf, "%s\n", buf);
}

ssize_t wdt_enable_set(struct device *dev, struct device_attribute *da, const char *buf, size_t count)
{
    int status = -EPERM;
    int value  = -EPERM;
    int result = -EPERM;
    int i;
    struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct Cameo_i2c_data *data = i2c_get_clientdata(Cameo_CPLD_30_client);
    
    mutex_lock(&data->update_lock);
    status = i2c_smbus_read_byte_data(Cameo_CPLD_30_client, WDT_EN_REG);
    if (attr->index == WDT_EN)
    {
        i = simple_strtol(buf, NULL, 10);
        if (i == ENABLE)
        {
            value = status | WDT_EN_ENABLE;
            result = i2c_smbus_write_byte_data(Cameo_CPLD_30_client, WDT_EN_REG, value);
            if (result < 0)
            {
                printk(KERN_ALERT "ERROR: WDT_EN_ENABLE FAILED!\n");
            }
        }
        else if (i == DISABLE)
        {
            value = status & WDT_EN_DISABLE;
            result = i2c_smbus_write_byte_data(Cameo_CPLD_30_client, WDT_EN_REG, value);
            if (result < 0)
            {
                printk(KERN_ALERT "ERROR:WDT_EN_DISABLE FAILED!\n");
            }
        }
        else
        {
            printk(KERN_ALERT "WDT_EN set wrong Value\n");
        }
    }
    mutex_unlock(&data->update_lock);
    return count;
}
ssize_t eeprom_wp_get(struct device *dev, struct device_attribute *da, char *buf)
{
    struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct Cameo_i2c_data *data = i2c_get_clientdata(Cameo_CPLD_30_client);
    
    mutex_lock(&data->update_lock);
    sprintf(buf, "");
    if (attr->index == EEPROM_WP)
    {
        if (i2c_smbus_read_byte_data(Cameo_CPLD_30_client, EEPROM_WP_REG) & BIT_2_MASK)
        {
            sprintf(buf, "%s%d\n", buf, ENABLE);
        }
        else
        {
            sprintf(buf, "%s%d\n", buf, DISABLE);
        }
    }
    mutex_unlock(&data->update_lock);
    return sprintf(buf, "%s\n", buf);
}
ssize_t eeprom_wp_set(struct device *dev, struct device_attribute *da, const char *buf, size_t count)
{
    int status = -EPERM;
    int value  = -EPERM;
    int result = -EPERM;
    int i;
    struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct Cameo_i2c_data *data = i2c_get_clientdata(Cameo_CPLD_30_client);
    
    mutex_lock(&data->update_lock);
    status = i2c_smbus_read_byte_data(Cameo_CPLD_30_client, EEPROM_WP_REG);
    if (attr->index == EEPROM_WP)
    {
        i = simple_strtol(buf, NULL, 10);
        if (i == ENABLE)
        {
            value = status | EEPROM_WP_ENABLE;
            result = i2c_smbus_write_byte_data(Cameo_CPLD_30_client, EEPROM_WP_REG, value);
            if (result < 0)
            {
                printk(KERN_ALERT "ERROR: EEPROM_WP_ENABLE FAILED!\n");
            }
        }
        else if (i == DISABLE)
        {
            value = status & EEPROM_WP_DISABLE;
            result = i2c_smbus_write_byte_data(Cameo_CPLD_30_client, EEPROM_WP_REG, value);
            if (result < 0)
            {
                printk(KERN_ALERT "ERROR:EEPROM_WP_DISABLE FAILED!\n");
            }
        }
        else
        {
            printk(KERN_ALERT "EEPROM_WP set wrong Value\n");
        }
    }
    mutex_unlock(&data->update_lock);
    return count;
}
ssize_t usb_enable_get(struct device *dev, struct device_attribute *da, char *buf)
{
    return sprintf(buf, "%s\n", buf);
}
ssize_t usb_enable_set(struct device *dev, struct device_attribute *da, const char *buf, size_t count)
{
    return count;
}
ssize_t reset_mac_set(struct device *dev, struct device_attribute *da, const char *buf, size_t count)
{
    return count;
}
ssize_t shutdown_set(struct device *dev, struct device_attribute *da, const char *buf, size_t count)
{
    return count;
}
ssize_t bmc_enable_get(struct device *dev, struct device_attribute *da, char *buf)
{
    return sprintf(buf, "%s\n", buf);
}
ssize_t themal_int_get(struct device *dev, struct device_attribute *da, char *buf)
{
    return sprintf(buf, "%s\n", buf);
}
ssize_t themal_int_mask_get(struct device *dev, struct device_attribute *da, char *buf)
{
    return sprintf(buf, "%s\n", buf);
}
ssize_t themal_int_mask_set(struct device *dev, struct device_attribute *da, const char *buf, size_t count)
{
    return count;
}
ssize_t sys_int_get(struct device *dev, struct device_attribute *da, char *buf)
{
    return sprintf(buf, "%s\n", buf);
}
ssize_t sys_int_mask_get(struct device *dev, struct device_attribute *da, char *buf)
{
    return sprintf(buf, "%s\n", buf);
}
ssize_t sys_int_mask_set(struct device *dev, struct device_attribute *da, const char *buf, size_t count)
{
    return count;
}
/* end of implement i2c_function */