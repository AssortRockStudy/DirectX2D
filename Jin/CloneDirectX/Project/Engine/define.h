#pragma once


#define SINGLETON(classtype)  	private:\
								classtype();\
								~classtype();\
							friend class CSingleton<classtype>;

#define DEVICE CDevice::GetInst()->GetDevice()
#define CONTEXT CDevice::GetInst()->GetContext()