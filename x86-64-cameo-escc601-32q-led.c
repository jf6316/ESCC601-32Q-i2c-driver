/* An hwmon driver for Cameo ESCC601-32Q Innovium i2c Module */
#pragma GCC diagnostic ignored "-Wformat-zero-length"
#include "x86-64-cameo-escc601-32q.h"
#include "x86-64-cameo-escc601-32q-common.h"
#include "x86-64-cameo-escc601-32q-led.h"

/* extern i2c_function */
/* end of extern i2c_function */

/* implement i2c_function */
ssize_t led_ctrl_get(struct device *dev, struct device_attribute *da, char *buf)
{
    return sprintf(buf, "%s\n", buf);
}
ssize_t led_ctrl_set(struct device *dev, struct device_attribute *da, const char *buf, size_t count)
{
    return count;
}
ssize_t led_fiber_get(struct device *dev, struct device_attribute *da, char *buf)
{
    return sprintf(buf, "%s\n", buf);
}
ssize_t led_fiber_set(struct device *dev, struct device_attribute *da, const char *buf, size_t count)
{
    return count;
}
/* end of implement i2c_function */