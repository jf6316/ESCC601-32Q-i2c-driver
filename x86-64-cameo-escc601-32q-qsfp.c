/* An hwmon driver for Cameo ESCC601-32Q Innovium i2c Module */
#pragma GCC diagnostic ignored "-Wformat-zero-length"
#include "x86-64-cameo-escc601-32q.h"
#include "x86-64-cameo-escc601-32q-common.h"
#include "x86-64-cameo-escc601-32q-qsfp.h"


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
    return sprintf(buf, "%s\n", buf);
}
ssize_t qsfp_low_power_set(struct device *dev, struct device_attribute *da, const char *buf, size_t count)
{
    return count;
}
ssize_t qsfp_reset_all_set(struct device *dev, struct device_attribute *da, const char *buf, size_t count)
{
    return count;
}
ssize_t qsfp_reset_set(struct device *dev, struct device_attribute *da, const char *buf, size_t count)
{
    return count;
}
ssize_t qsfp_present_all_get(struct device *dev, struct device_attribute *da, char *buf)
{
    return sprintf(buf, "%s\n", buf);
}
ssize_t qsfp_present_get(struct device *dev, struct device_attribute *da, char *buf)
{
    return sprintf(buf, "%s\n", buf);
}
ssize_t qsfp_int_all_get(struct device *dev, struct device_attribute *da, char *buf)
{
    return sprintf(buf, "%s\n", buf);
}
ssize_t qsfp_int_get(struct device *dev, struct device_attribute *da, char *buf)
{
    return sprintf(buf, "%s\n", buf);
}
ssize_t qsfp_quter_int_get(struct device *dev, struct device_attribute *da, char *buf)
{
    return sprintf(buf, "%s\n", buf);
}
ssize_t qsfp_quter_int_mask_get(struct device *dev, struct device_attribute *da, char *buf)
{
    return sprintf(buf, "%s\n", buf);
}
ssize_t qsfp_quter_int_mask_set(struct device *dev, struct device_attribute *da, const char *buf, size_t count)
{
    return count;
}
ssize_t qsfp_modprs_int_get(struct device *dev, struct device_attribute *da, char *buf)
{
    return sprintf(buf, "%s\n", buf);
}
ssize_t qsfp_modprs_int_mask_get(struct device *dev, struct device_attribute *da, char *buf)
{
    return sprintf(buf, "%s\n", buf);
}
ssize_t qsfp_modprs_int_mask_set(struct device *dev, struct device_attribute *da, const char *buf, size_t count)
{
    return count;
}
/* end of implement i2c_function */