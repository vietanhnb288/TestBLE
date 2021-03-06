
#include <stdint.h>
#include <string.h>
#include "nrf_gpio.h"
#include "our_service.h"
#include "ble_srv_common.h"
#include "app_error.h"

// ALREADY_DONE_FOR_YOU: Declaration of a function that will take care of some housekeeping of ble connections related to our service and characteristic
void ble_our_service_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
  	ble_os_t * p_our_service =(ble_os_t *) p_context;  
		// OUR_JOB: Step 3.D Implement switch case handling BLE events related to our service. 
	
	
}
//static void da_ghi(ble_os_t * p_our_service, ble_evt_t const * p_ble_evt)
//{
//    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;
//    if (   (p_evt_write->handle == p_our_service->char_handles.value_handle)
//        && (p_evt_write->len == 1)
//        && (p_our_service->plug_write_handler != NULL))
//    {
//        p_our_service->plug_write_handler(p_ble_evt->evt.gap_evt.conn_handle, p_our_service, p_evt_write->data[0]);
//    }
//}

//void ble_our_service_on_ble_evt_1(ble_evt_t const * p_ble_evt, void * p_context)
//{
//  	ble_os_t * p_our_service =(ble_os_t *) p_context;  
//		// OUR_JOB: Step 3.D Implement switch case handling BLE events related to our service. 
//		switch(p_ble_evt->header.evt_id)
//		{
//			case BLE_GAP_EVT_CONNECTED:
//				p_our_service->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
//			break;
//			case BLE_GAP_EVT_DISCONNECTED:
//				p_our_service->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;			
//			break;
//			case BLE_GATTS_EVT_WRITE:
//				da_ghi(p_our_service, p_ble_evt); // mode 2
//			break;
//			default:
//				break;
//		}
//}

void ble_our_service_on_ble_evt_2(ble_evt_t const * p_ble_evt, void * p_context)
{
  	ble_os_t * p_our_service =(ble_os_t *) p_context;  
		// OUR_JOB: Step 3.D Implement switch case handling BLE events related to our service. 
		switch(p_ble_evt->header.evt_id)
		{
			case BLE_GAP_EVT_CONNECTED:
				p_our_service->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
			break;
			case BLE_GAP_EVT_DISCONNECTED:
				p_our_service->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;			
			break;
			case BLE_GATTS_EVT_WRITE:
				// do nothing 
			break;
			default:
				break;
		}
}

//void ble_our_service_on_ble_evt_3(ble_evt_t const * p_ble_evt, void * p_context)
//{
//  	ble_os_t * p_our_service =(ble_os_t *) p_context;  
//		// OUR_JOB: Step 3.D Implement switch case handling BLE events related to our service. 
//		switch(p_ble_evt->header.evt_id)
//		{
//			case BLE_GAP_EVT_CONNECTED:
//				p_our_service->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
//			break;
//			case BLE_GAP_EVT_DISCONNECTED:
//				p_our_service->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;			
//			break;
//			case BLE_GATTS_EVT_WRITE:
//				da_ghi(p_our_service, p_ble_evt); // su kien chuyen mode
//			break;
//			default:
//				break;
//		}
//}

/**@brief Function for adding our new characterstic to "Our service" that we initiated in the previous tutorial. 
 *
 * @param[in]   p_our_service        Our Service structure.
 *
 */
// static uint32_t our_char_add(ble_os_t * p_our_service,ble_uuid128_t service_uuid_128, uint16_t char_uuid_16, uint8_t length, uint8_t *value)
static uint32_t our_char_add_1(ble_os_t * p_our_service)
{
    // OUR_JOB: Step 2.A, Add a custom characteristic UUID
			uint32_t            err_code;
			ble_uuid_t          char_uuid;
			ble_uuid128_t       base_uuid = BLE_UUID_OUR_BASE_UUID;
			char_uuid.uuid      = BLE_UUID_OUR_CHARACTERISTC_UUID;
			err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid.type);
			APP_ERROR_CHECK(err_code); 		 
    
    // OUR_JOB: Step 2.F Add read/write properties to our characteristic

			ble_gatts_char_md_t char_md;
			memset(&char_md, 0, sizeof(char_md));
			char_md.char_props.read = 1;
			char_md.char_props.write = 1;

    // OUR_JOB: Step 3.A, Configuring Client Characteristic Configuration Descriptor metadata and add to char_md structure
    ble_gatts_attr_md_t cccd_md;
    memset(&cccd_md, 0, sizeof(cccd_md));
    
    // OUR_JOB: Step 2.B, Configure the attribute metadata
    ble_gatts_attr_md_t attr_md;
    memset(&attr_md, 0, sizeof(attr_md)); 
		attr_md.vloc = BLE_GATTS_VLOC_STACK;
		
    // OUR_JOB: Step 2.G, Set read/write security levels to our characteristic
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    
    // OUR_JOB: Step 2.C, Configure the characteristic value attribute
    ble_gatts_attr_t    attr_char_value;
    memset(&attr_char_value, 0, sizeof(attr_char_value));
		attr_char_value.p_uuid      = &char_uuid;
		attr_char_value.p_attr_md   = &attr_md;
    
    // OUR_JOB: Step 2.H, Set characteristic length in number of bytes
		attr_char_value.max_len = 4;
		attr_char_value.init_len = 4;
		uint8_t value[4]            = {0x12,0x34,0x56,0x78};
		attr_char_value.p_value = value;    

		err_code = sd_ble_gatts_characteristic_add(p_our_service->service_handle,
																			 &char_md,
																			 &attr_char_value,
																			 &p_our_service->char_handles_1);
		APP_ERROR_CHECK(err_code);																										


    // OUR_JOB: Step 2.E, Add our new characteristic to the service


    return NRF_SUCCESS;
}
static uint32_t our_char_add_2(ble_os_t * p_our_service)
{
    // OUR_JOB: Step 2.A, Add a custom characteristic UUID
			uint32_t            err_code;
			ble_uuid_t          char_uuid;
			ble_uuid128_t       base_uuid = BLE_UUID_OUR_BASE_UUID;
			char_uuid.uuid      = BLE_UUID_ADE_CHARACTERISTC_UUID;
			err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid.type);
			APP_ERROR_CHECK(err_code); 		 
    
    // OUR_JOB: Step 2.F Add read/write properties to our characteristic

			ble_gatts_char_md_t char_md;
			memset(&char_md, 0, sizeof(char_md));
			char_md.char_props.read = 1;
			char_md.char_props.write = 1;

    // OUR_JOB: Step 3.A, Configuring Client Characteristic Configuration Descriptor metadata and add to char_md structure
    ble_gatts_attr_md_t cccd_md;
    memset(&cccd_md, 0, sizeof(cccd_md));
    
    // OUR_JOB: Step 2.B, Configure the attribute metadata
    ble_gatts_attr_md_t attr_md;
    memset(&attr_md, 0, sizeof(attr_md)); 
		attr_md.vloc = BLE_GATTS_VLOC_STACK;
		
    // OUR_JOB: Step 2.G, Set read/write security levels to our characteristic
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    
    // OUR_JOB: Step 2.C, Configure the characteristic value attribute
    ble_gatts_attr_t    attr_char_value;
    memset(&attr_char_value, 0, sizeof(attr_char_value));
		attr_char_value.p_uuid      = &char_uuid;
		attr_char_value.p_attr_md   = &attr_md;
    
    // OUR_JOB: Step 2.H, Set characteristic length in number of bytes
		attr_char_value.max_len = 4;
		attr_char_value.init_len = 4;
		uint8_t value[4]            = {0x12,0x34,0x56,0x78};
		attr_char_value.p_value = value;    

		err_code = sd_ble_gatts_characteristic_add(p_our_service->service_handle,
																			 &char_md,
																			 &attr_char_value,
																			 &p_our_service->char_handles_2);
		APP_ERROR_CHECK(err_code);																										


    // OUR_JOB: Step 2.E, Add our new characteristic to the service


    return NRF_SUCCESS;
}
static uint32_t our_char_add(ble_os_t * p_our_service)
{
    // OUR_JOB: Step 2.A, Add a custom characteristic UUID
			uint32_t            err_code;
			ble_uuid_t          char_uuid;
			ble_uuid128_t       base_uuid = BLE_UUID_CTRL_BASE_UUID ;
			char_uuid.uuid      = BLE_UUID_CTRL_CHARACTERISTC_UUID;
			err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid.type);
			APP_ERROR_CHECK(err_code); 		 
    
    // OUR_JOB: Step 2.F Add read/write properties to our characteristic

			ble_gatts_char_md_t char_md;
			memset(&char_md, 0, sizeof(char_md));
			char_md.char_props.read = 1;
			char_md.char_props.write = 1;

    // OUR_JOB: Step 3.A, Configuring Client Characteristic Configuration Descriptor metadata and add to char_md structure
    ble_gatts_attr_md_t cccd_md;
    memset(&cccd_md, 0, sizeof(cccd_md));
    
    // OUR_JOB: Step 2.B, Configure the attribute metadata
    ble_gatts_attr_md_t attr_md;
    memset(&attr_md, 0, sizeof(attr_md)); 
		attr_md.vloc = BLE_GATTS_VLOC_STACK;
		
    // OUR_JOB: Step 2.G, Set read/write security levels to our characteristic
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    
    // OUR_JOB: Step 2.C, Configure the characteristic value attribute
    ble_gatts_attr_t    attr_char_value;
    memset(&attr_char_value, 0, sizeof(attr_char_value));
		attr_char_value.p_uuid      = &char_uuid;
		attr_char_value.p_attr_md   = &attr_md;
    
    // OUR_JOB: Step 2.H, Set characteristic length in number of bytes
		attr_char_value.max_len = 4;
		attr_char_value.init_len = 4;
		uint8_t value[4]            = {0x12,0x34,0x56,0x78};
		attr_char_value.p_value = value;    

		err_code = sd_ble_gatts_characteristic_add(p_our_service->service_handle,
																			 &char_md,
																			 &attr_char_value,
																			 &p_our_service->char_handles);
		APP_ERROR_CHECK(err_code);																										


    // OUR_JOB: Step 2.E, Add our new characteristic to the service


    return NRF_SUCCESS;
}

/**@brief Function for initiating our new service.
 *
 * @param[in]   p_our_service        Our Service structure.
 *
 */
//void our_service_init(ble_os_t * p_our_service, ble_uuid128_t service_uuid_128, uint16_t service_uuid16, uint16_t char_uuid16, uint8_t length, uint8_t *value)
void our_service_init_1(ble_os_t * p_our_service)
{
    uint32_t   err_code; // Variable to hold return codes from library and softdevice functions

    // FROM_SERVICE_TUTORIAL: Declare 16-bit service and 128-bit base UUIDs and add them to the BLE stack
    ble_uuid_t        service_uuid;
    ble_uuid128_t     base_uuid = BLE_UUID_OUR_BASE_UUID;
    service_uuid.uuid = BLE_UUID_OUR_SERVICE_UUID;
    err_code = sd_ble_uuid_vs_add(&base_uuid, &service_uuid.type);
    APP_ERROR_CHECK(err_code);    
    
    // OUR_JOB: Step 3.B, Set our service connection handle to default value. I.e. an invalid handle since we are not yet in a connection.
	
    p_our_service->conn_handle = BLE_CONN_HANDLE_INVALID;
    // FROM_SERVICE_TUTORIAL: Add our service
		err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &service_uuid,
                                        &p_our_service->service_handle);
    
    APP_ERROR_CHECK(err_code);
    
    // OUR_JOB: Call the function our_char_add() to add our new characteristic to the service. 
    our_char_add_1(p_our_service);
		our_char_add_2(p_our_service);
}

void our_service_init_2(ble_os_t * p_our_service)
{
	    uint32_t   err_code; // Variable to hold return codes from library and softdevice functions

    // FROM_SERVICE_TUTORIAL: Declare 16-bit service and 128-bit base UUIDs and add them to the BLE stack
    ble_uuid_t        service_uuid;
    ble_uuid128_t     base_uuid = BLE_UUID_CTRL_BASE_UUID;
    service_uuid.uuid = BLE_UUID_CTRL_SERVICE_UUID;
    err_code = sd_ble_uuid_vs_add(&base_uuid, &service_uuid.type);
    APP_ERROR_CHECK(err_code);    
    
    // OUR_JOB: Step 3.B, Set our service connection handle to default value. I.e. an invalid handle since we are not yet in a connection.
	
    p_our_service->conn_handle = BLE_CONN_HANDLE_INVALID;
    // FROM_SERVICE_TUTORIAL: Add our service
		err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &service_uuid,
                                        &p_our_service->service_handle);
    
    APP_ERROR_CHECK(err_code);
    
    // OUR_JOB: Call the function our_char_add() to add our new characteristic to the service. 
    our_char_add(p_our_service);
}
// ALREADY_DONE_FOR_YOU: Function to be called when updating characteristic value
void value_characteristic_update(ble_os_t *p_our_service, uint32_t *myvalue)
{
    // OUR_JOB: Step 3.E, Update characteristic value
		
{
    // Send value if connected and notifying
    if (p_our_service->conn_handle != BLE_CONN_HANDLE_INVALID)
    {
        uint16_t               len = 4;
        ble_gatts_hvx_params_t hvx_params;
        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = p_our_service->char_handles_1.value_handle;
        hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset = 0;
        hvx_params.p_len  = &len;
        hvx_params.p_data = (uint8_t*)myvalue;  

        sd_ble_gatts_hvx(p_our_service->conn_handle, &hvx_params);
    }  
}   

// Store current temperature value until next updated. 

}
