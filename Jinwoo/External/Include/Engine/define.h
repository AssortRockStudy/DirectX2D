#pragma once

#define SINGLE(classtype) private:\
							classtype();\
							~classtype();\
							friend class CSingleton<classtype>;

#define DEVICE CDevice::GetInst()->GetDevice()
#define CONTEXT CDevice::GetInst()->GetContext()

#define KEY_CHECK(Key, State) MyKeyMgr::GetInst()->GetKeyState(KEY::Key) == KEY_STATE::State

#define KEY_TAP(Key)		KEY_CHECK(Key, TAP)
#define KEY_PRESSED(Key)	KEY_CHECK(Key, PRESSED)
#define KEY_RELEASED(Key)	KEY_CHECK(Key, RELEASED)
#define KEY_NONE(Key)		KEY_CHECK(Key, NONE)

#define PI 3.14159265358979f

#define DT MyTimeMgr::GetInst()->GetDeltaTime()