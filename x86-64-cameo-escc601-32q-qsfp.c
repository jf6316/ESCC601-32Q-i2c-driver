/* An hwmon driver for Cameo ESCC601-32Q Innovium i2c Module */
#pragma GCC diagnostic ignored "-Wformat-zero-length"
#include "x86-64-cameo-escc601-32q.h"
#include "x86-64-cameo-escc601-32q-common.h"
#include "x86-64-cameo-escc601-32q-qsfp.h"

/* i2c_client Declaration */
extern struct i2c_client *Cameo_CPLD_31_client; //0x31 for Port 01-16
extern struct i2c_client *Cameo_CPLD_32_client; //0x32 for Port 17-32
/* end of i2c_client Declaration */

/* extern i2c_function */
/* end of extern i2c_function */

/* implement i2c_function */
ssize_t qsfp_low_power_all_get(struct device *dev, struct device_attribute *da, char *buf)
{
    return sprintf(buf, "%s\n", buf);
}

ssize_t qsfp_low_power_all_set(struct device *dev, struct device_attribute *da, const char *buf, size_t count)
{
    return count;
}

ssize_t qsfp_low_power_get(struct device *dev, struct device_attribute *da, char *buf)
{
    int status = -EPERM;
    int port_index = 0;
    struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
    
    port_index = attr->index;
    sprintf(buf, "");

    if (port_index >= 1 && port_index <= 16)
    {
        status = i2c_smbus_read_byte_data(Cameo_CPLD_31_client, qsfp_low_power_regs[port_index][0]);
    }
    else if (port_index >= 17 && port_index <= 32)
    {
        status = i2c_smbus_read_byte_data(Cameo_CPLD_32_client, qsfp_low_power_regs[port_index][0]);
    }
    
    if (status & qsfp_low_power_regs[port_index][1])
    {
        sprintf(buf, "%s%d\n", buf, ENABLE);
    }
    else
    {
        sprintf(buf, "%s%d\n", buf, DISABLE);
    }
    
    return sprintf(buf, "%s\n", buf);
}

ssize_t qsfp_low_power_set(struct device *dev, struct device_attribute *da, const char *buf, size_t count)
{
    int status = -EPERM;
    int result = 0;
    int input  = 0;
    int port_index = 0;
    struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct Cameo_i2c_data *Cameo_CPLD_31_data = i2c_get_clientdata(Cameo_CPLD_31_client);
	struct Cameo_i2c_data *Cameo_CPLD_32_data = i2c_get_clientdata(Cameo_CPLD_32_client);
    struct i2c_client *target_client = NULL; 
    
    port_index = attr->index;
    input = simple_strtol(buf, NULL, 10);
    mutex_lock(&Cameo_CPLD_31_data->update_lock);
    mutex_lock(&Cameo_CPLD_32_data->update_lock);

    if (port_index >= 1 && port_index <= 16)
    {
        target_client = Cameo_CPLD_31_client;

    }
    else if (port_index >= 17 && port_index <= 32)
    {
        target_client = Cameo_CPLD_32_client;
    }
    
    status = i2c_smbus_read_byte_data(target_client, qsfp_low_power_regs[port_index][0]);
    if( input == ENABLE)
    {
        status |= qsfp_low_power_regs[port_index][1];
        result = i2c_smbus_write_byte_data(target_client, qsfp_low_power_regs[port_index][0], status);
        if (result < 0)
        {
            printk(KERN_ALERT "ERROR: qsfp_low_power_set ON FAILED!\n");
        }
    }
    else if( input == DISABLE)
    {
        status &= ~(qsfp_low_power_regs[port_index][1]);
        result = i2c_smbus_write_byte_data(target_client, qsfp_low_power_regs[port_index][0], status);
        if (result < 0)
        {
            printk(KERN_ALERT "ERROR: qsfp_low_power_set OFF FAILED!\n");
        }
    }
    else
    {
        printk(KERN_ALERT "ERROR: qsfp_low_power_set WRONG VALUE\n");
    }
    
    mutex_unlock(&Cameo_CPLD_31_data->update_lock);
    mutex_unlock(&Cameo_CPLD_32_data->update_lock);
    
    return count;
}

ssize_t qsfp_reset_all_set(struct device *dev, struct device_attribute *da, const char *buf, size_t count)
{
    return count;
}

ssize_t qsfp_reset_set(struct device *dev, struct device_attribute *da, const char *buf, size_t count)
{
    int status = -EPERM;
    int result = 0;
    int input  = 0;
    int port_index = 0;
    struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct Cameo_i2c_data *Cameo_CPLD_31_data = i2c_get_clientdata(Cameo_CPLD_31_client);
	struct Cameo_i2c_data *Cameo_CPLD_32_data = i2c_get_clientdata(Cameo_CPLD_32_client);
    struct i2c_client *target_client = NULL; 
    
    port_index = attr->index;
    input = simple_strtol(buf, NULL, 10);
    mutex_lock(&Cameo_CPLD_31_data->update_lock);
    mutex_lock(&Cameo_CPLD_32_data->update_lock);

    if (port_index >= 1 && port_index <= 16)
    {
        target_client = Cameo_CPLD_31_client;

    }
    else if (port_index >= 17 && port_index <= 32)
    {
        target_client = Cameo_CPLD_32_client;
    }
    
    status = i2c_smbus_read_byte_data(target_client, qsfp_reset_regs[port_index][0]);
    if( input == ENABLE)
    {
        status |= qsfp_reset_regs[port_index][1];
        result = i2c_smbus_write_byte_data(target_client, qsfp_reset_regs[port_index][0], status);
        if (result < 0)
        {
            printk(KERN_ALERT "ERROR: qsfp_reset_set ON FAILED!\n");
        }
    }
    else
    {
        printk(KERN_ALERT "ERROR: qsfp_reset_set WRONG VALUE\n");
    }
    
    mutex_unlock(&Cameo_CPLD_31_data->update_lock);
    mutex_unlock(&Cameo_CPLD_32_data->update_lock);
    
    return count;
}

ssize_t qsfp_present_all_get(struct device *dev, struct device_attribute *da, char *buf)
{
    return sprintf(buf, "%s\n", buf);
}

ssize_t qsfp_present_get(struct device *dev, struct device_attribute *da, char *buf)
{
    int status = -EPERM;
    int port_index = 0;
    struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
    
    port_index = attr->index;
    sprintf(buf, "");

    if (port_index >= 1 && port_index <= 16)
    {
        status = i2c_smbus_read_byte_data(Cameo_CPLD_31_client, qsfp_present_regs[port_index][0]);
    }
    else if (port_index >= 17 && port_index <= 32)
    {
        status = i2c_smbus_read_byte_data(Cameo_CPLD_32_client, qsfp_present_regs[port_index][0]);
    }
    
    if (status & qsfp_present_regs[port_index][1])
    {
        sprintf(buf, "%s%d\n", buf, ENABLE);
    }
    else
    {
        sprintf(buf, "%s%d\n", buf, DISABLE);
    }
    
    return sprintf(buf, "%s\n", buf);
}
ssize_t qsfp_int_all_get(struct device *dev, struct device_attribute *da, char *buf)
{
    return sprintf(buf, "%s\n", buf);
}
ssize_t qsfp_int_get(struct device *dev, struct device_attribute *da, char *buf)
{
    int status = -EPERM;
    int port_index = 0;
    struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
    
    port_index = attr->index;
    sprintf(buf, "");

    if (port_index >= 1 && port_index <= 16)
    {
        status = i2c_smbus_read_byte_data(Cameo_CPLD_31_client, qsfp_int_regs[port_index][0]);
    }
    else if (port_index >= 17 && port_index <= 32)
    {
        status = i2c_smbus_read_byte_data(Cameo_CPLD_32_client, qsfp_int_regs[port_index][0]);
    }
    
    if (status & qsfp_int_regs[port_index][1])
    {
        sprintf(buf, "%s%d\n", buf, ENABLE);
    }
    else
    {
        sprintf(buf, "%s%d\n", buf, DISABLE);
    }
    
    return sprintf(buf, "%s\n", buf);
}

ssize_t qsfp_quter_int_get(struct device *dev, struct device_attribute *da, char *buf)
{
    int status = -EPERM;
    int quter_index = 0;
    struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
    
    quter_index = attr->index;
    sprintf(buf, "");

    if (quter_index >= 1 && quter_index <= 2)
    {
        status = i2c_smbus_read_byte_data(Cameo_CPLD_31_client, qsfp_quter_int_regs[quter_index][0]);
    }
    else if (quter_index >= 3 && quter_index <= 4)
    {
        status = i2c_smbus_read_byte_data(Cameo_CPLD_32_client, qsfp_quter_int_regs[quter_index][0]);
    }
    
    if (status & qsfp_quter_int_regs[quter_index][1])
    {
        sprintf(buf, "%s%d\n", buf, NORMAL);
    }
    else
    {
        sprintf(buf, "%s%d\n", buf, ABNORMAL);
    }
    
    return sprintf(buf, "%s\n", buf);
}

ssize_t qsfp_quter_int_mask_get(struct device *dev, struct device_attribute *da, char *buf)
{
    int status = -EPERM;
    int quter_index = 0;
    struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
    
    quter_index = attr->index;
    sprintf(buf, "");

    if (quter_index >= 1 && quter_index <= 2)
    {
        status = i2c_smbus_read_byte_data(Cameo_CPLD_31_client, qsfp_quter_int_mask_regs[quter_index][0]);
    }
    else if (quter_index >= 3 && quter_index <= 4)
    {
        status = i2c_smbus_read_byte_data(Cameo_CPLD_32_client, qsfp_quter_int_mask_regs[quter_index][0]);
    }
    
    if (status & qsfp_quter_int_mask_regs[quter_index][1])
    {
        sprintf(buf, "%s%d\n", buf, DISABLE);
    }
    else
    {
        sprintf(buf, "%s%d\n", buf, ENABLE);
    }
    
    return sprintf(buf, "%s\n", buf);
}

ssize_t qsfp_quter_int_mask_set(struct device *dev, struct device_attribute *da, const char *buf, size_t count)
{
    int status = -EPERM;
    int result = 0;
    int input  = 0;
    int quter_index = 0;
    struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct Cameo_i2c_data *Cameo_CPLD_31_data = i2c_get_clientdata(Cameo_CPLD_31_client);
	struct Cameo_i2c_data *Cameo_CPLD_32_data = i2c_get_clientdata(Cameo_CPLD_32_client);
    struct i2c_client *target_client = NULL; 
    
    quter_index = attr->index;
    input = simple_strtol(buf, NULL, 10);
    mutex_lock(&Cameo_CPLD_31_data->update_lock);
    mutex_lock(&Cameo_CPLD_32_data->update_lock);

    if (quter_index >= 1 && quter_index <= 2)
    {
        target_client = Cameo_CPLD_31_client;

    }
    else if (quter_index >= 3 && quter_index <= 4)
    {
        target_client = Cameo_CPLD_32_client;
    }
    
    status = i2c_smbus_read_byte_data(target_client, qsfp_quter_int_mask_regs[quter_index][0]);
    if( input == DISABLE)
    {
        status |= qsfp_quter_int_mask_regs[quter_index][1];
        result = i2c_smbus_write_byte_data(target_client, qsfp_quter_int_mask_regs[quter_index][0], status);
        if (result < 0)
        {
            printk(KERN_ALERT "ERROR: qsfp_quter_int_mask_set ON FAILED!\n");
        }
    }
    else if( input == ENABLE)
    {
        status &= ~(qsfp_quter_int_mask_regs[quter_index][1]);
        result = i2c_smbus_write_byte_data(target_client, qsfp_quter_int_mask_regs[quter_index][0], status);
        if (result < 0)
        {
            printk(KERN_ALERT "ERROR: qsfp_quter_int_mask_set OFF FAILED!\n");
        }
    }
    else
    {
        printk(KERN_ALERT "ERROR: qsfp_quter_int_mask_set WRONG VALUE\n");
    }
    
    mutex_unlock(&Cameo_CPLD_31_data->update_lock);
    mutex_unlock(&Cameo_CPLD_32_data->update_lock);
    
    return count;
}

ssize_t qsfp_modprs_int_get(struct device *dev, struct device_attribute *da, char *buf)
{
    int status = -EPERM;
    int quter_index = 0;
    struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
    
    quter_index = attr->index;
    sprintf(buf, "");

    if (quter_index >= 1 && quter_index <= 2)
    {
        status = i2c_smbus_read_byte_data(Cameo_CPLD_31_client, qsfp_modprs_int_regs[quter_index][0]);
    }
    else if (quter_index >= 3 && quter_index <= 4)
    {
        status = i2c_smbus_read_byte_data(Cameo_CPLD_32_client, qsfp_modprs_int_regs[quter_index][0]);
    }
    
    if (status & qsfp_modprs_int_regs[quter_index][1])
    {
        sprintf(buf, "%s%d\n", buf, NORMAL);
    }
    else
    {
        sprintf(buf, "%s%d\n", buf, ABNORMAL);
    }
    
    return sprintf(buf, "%s\n", buf);
}

ssize_t qsfp_modprs_int_mask_get(struct device *dev, struct device_attribute *da, char *buf)
{
    int status = -EPERM;
    int quter_index = 0;
    struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
    
    quter_index = attr->index;
    sprintf(buf, "");

    if (quter_index >= 1 && quter_index <= 2)
    {
        status = i2c_smbus_read_byte_data(Cameo_CPLD_31_client, qsfp_modprs_int_mask_regs[quter_index][0]);
    }
    else if (quter_index >= 3 && quter_index <= 4)
    {
        status = i2c_smbus_read_byte_data(Cameo_CPLD_32_client, qsfp_modprs_int_mask_regs[quter_index][0]);
    }
    
    if (status & qsfp_modprs_int_mask_regs[quter_index][1])
    {
        sprintf(buf, "%s%d\n", buf, DISABLE);
    }
    else
    {
        sprintf(buf, "%s%d\n", buf, ENABLE);
    }
    
    return sprintf(buf, "%s\n", buf);
}

ssize_t qsfp_modprs_int_mask_set(struct device *dev, struct device_attribute *da, const char *buf, size_t count)
{
    int status = -EPERM;
    int result = 0;
    int input  = 0;
    int quter_index = 0;
    struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct Cameo_i2c_data *Cameo_CPLD_31_data = i2c_get_clientdata(Cameo_CPLD_31_client);
	struct Cameo_i2c_data *Cameo_CPLD_32_data = i2c_get_clientdata(Cameo_CPLD_32_client);
    struct i2c_client *target_client = NULL; 
    
    quter_index = attr->index;
    input = simple_strtol(buf, NULL, 10);
    mutex_lock(&Cameo_CPLD_31_data->update_lock);
    mutex_lock(&Cameo_CPLD_32_data->update_lock);

    if (quter_index >= 1 && quter_index <= 2)
    {
        target_client = Cameo_CPLD_31_client;

    }
    else if (quter_index >= 3 && quter_index <= 4)
    {
        target_client = Cameo_CPLD_32_client;
    }
    
    status = i2c_smbus_read_byte_data(target_client, qsfp_modprs_int_mask_regs[quter_index][0]);
    if( input == DISABLE)
    {
        status |= qsfp_modprs_int_mask_regs[quter_index][1];
        result = i2c_smbus_write_byte_data(target_client, qsfp_modprs_int_mask_regs[quter_index][0], status);
        if (result < 0)
        {
            printk(KERN_ALERT "ERROR: qsfp_modprs_int_mask_set ON FAILED!\n");
        }
    }
    else if( input == ENABLE)
    {
        status &= ~(qsfp_modprs_int_mask_regs[quter_index][1]);
        result = i2c_smbus_write_byte_data(target_client, qsfp_modprs_int_mask_regs[quter_index][0], status);
        if (result < 0)
        {
            printk(KERN_ALERT "ERROR: qsfp_modprs_int_mask_set OFF FAILED!\n");
        }
    }
    else
    {
        printk(KERN_ALERT "ERROR: qsfp_modprs_int_mask_set WRONG VALUE\n");
    }
    
    mutex_unlock(&Cameo_CPLD_31_data->update_lock);
    mutex_unlock(&Cameo_CPLD_32_data->update_lock);
    
    return count;
}
/* end of implement i2c_function */