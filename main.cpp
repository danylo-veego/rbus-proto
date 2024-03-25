#include <rbus/rbus.h>

#include <cstdio>
#include <rbus/rbus_value.h>

rbusError_t get_handler(rbusHandle_t handle, rbusProperty_t property, rbusGetHandlerOptions_t* options)
{
  fprintf(stderr, "get_value\n");

  //rbusProperty_GetName(property);

  rbusValue_t value;
  rbusValue_Init(&value);
  rbusValue_SetString(value, "foobar");
  rbusProperty_SetValue(property, value);
  rbusValue_Release(value);

  return RBUS_ERROR_SUCCESS;
}

int main(int argc, char *argv[])
{
  rbusHandle_t rbus_handle;
  
  if (const rbusError_t open_error = rbus_open(&rbus_handle, "QoS"); open_error != RBUS_ERROR_SUCCESS)
  {
    fprintf(stderr, "Failed to open RBUS: %d\n", open_error);
    return open_error;
  }

  rbusDataElement_t data_elements[] = {{"Sandbox.QoS", RBUS_ELEMENT_TYPE_PROPERTY, {get_handler, nullptr, nullptr, nullptr, nullptr, nullptr}}};
  
  if (const rbusError_t register_error = rbus_regDataElements(rbus_handle, sizeof(data_elements)/sizeof(rbusDataElement_t), data_elements);
    register_error != RBUS_ERROR_SUCCESS)
  {
    fprintf(stderr, "Failed to register data element: %d\n", register_error);
    return register_error;
  }

  if (const rbusError_t close_error = rbus_close(rbus_handle); close_error != RBUS_ERROR_SUCCESS)
  {
    fprintf(stderr, "o_O Failed to close RBUS: %d\n", close_error);
    return close_error;
  }

  return 0;
}