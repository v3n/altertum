#ifdef _WIN32
#include <windows.h>
#include <XInput.h>
#endif

#define WIN32_LEAN_AND_MEAN
#include "../src/math/math_types.h" //Only used for x/y values of sticks

/*
Button bitmasks, according to:
https://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.xinput_gamepad(v=vs.85).aspx

XINPUT_GAMEPAD_DPAD_UP          0x0001
XINPUT_GAMEPAD_DPAD_DOWN        0x0002
XINPUT_GAMEPAD_DPAD_LEFT        0x0004
XINPUT_GAMEPAD_DPAD_RIGHT       0x0008
XINPUT_GAMEPAD_START            0x0010
XINPUT_GAMEPAD_BACK             0x0020
XINPUT_GAMEPAD_LEFT_THUMB       0x0040
XINPUT_GAMEPAD_RIGHT_THUMB      0x0080
XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
XINPUT_GAMEPAD_A                0x1000
XINPUT_GAMEPAD_B                0x2000
XINPUT_GAMEPAD_X                0x4000
XINPUT_GAMEPAD_Y                0x8000

Ranges for undefined controller members
bLeftTrigger:		0 to 255
bRightTrigger:		0 to 255
sThumbLX:			-32768 to 32767
sThumbLY:			-32768 to 32767
sThumbRX:			-32768 to 32767
sThumbRY:			-32768 to 32767
*/

namespace altertum
{
	struct xbox_gamepad
	{
		gamepad::gamepad_state state;
		gamepad::GP_INDEX pad_index;
		XINPUT_STATE xstate;
	};
namespace gamepad
{
#define GP_BUTTON_COUNT 15 //15 buttons on the 360 controller
	
	//simple button enum
	typedef enum
	{
		DPAD_UP = 0,
		DPAD_DOWN = 1,
		DPAD_LEFT = 2,
		DPAD_RIGHT = 3,
		START = 4,
		BACK = 5,
		L_THUMB = 6,
		R_THUMB = 7,
		L_BUMPER = 8,
		R_BUMPER = 9,
		A = 10,
		B = 11,
		X = 12,
		Y = 13,
		GUIDE = 14
	}GP_BUTTON;

	//simple gamepad index enum
	typedef enum
	{
		PAD_ONE = 0,
		PAD_TWO = 1,
		PAD_THREE = 2,
		PAD_FOUR = 3
	}GP_INDEX;

	
	struct gamepad_state//WIP
	{
		bool buttons[GP_BUTTON_COUNT]; 
		altertum::Vector2 lstick_xy, rstick_xy; //Left and right thumbstick x and y values
		float left_trigger, right_trigger;
		void reset()
		{
			for (int i = 0; i < GP_BUTTON_COUNT; i++)
				buttons[i] = false;
			
			lstick_xy.x = 0.0f; lstick_xy.y = 0.0f;
			rstick_xy.x = 0.0f; rstick_xy.y = 0.0f;
			left_trigger = 0.0f; right_trigger = 0.0f;
		}
	};

	/**Returns true if a gamepad is connected, false otherwise.*/
	bool connected(altertum::xbox_gamepad & pad)
	{
		//zero out the state
		memset(&pad.xstate,0, sizeof(XINPUT_STATE));
		
		//get the state of the controller
		DWORD result = XInputGetState(pad.pad_index, &pad.xstate);
		
		if (result == ERROR_SUCCESS)
			return true;
		else
			return false;
	}

	/**Constructs and returns a new instance of an xbox_gamepad.
		@param player_num: Note this should be in the range of 1 - 4, not 0 - 3
	*/
	altertum::xbox_gamepad xbox_gamepad(int player_num)//WIP
	{
		altertum::xbox_gamepad pad;
		switch (player_num)
		{
		case 1:
			pad.pad_index = GP_INDEX::PAD_ONE;
			break;
		case 2:
			pad.pad_index = GP_INDEX::PAD_TWO;
			break;
		case 3:
			pad.pad_index = GP_INDEX::PAD_THREE;
			break;
		case 4:
			pad.pad_index = GP_INDEX::PAD_FOUR;
			break;
		default://TODO: add error logic
			break;
		}
		return pad;
	}

	/** Sets the vibration speed for @param pad with distinct values for the left and right
		vibration motors @param left_speed @param right_speed.*/
	void vibrate(int left_speed, int right_speed, altertum::xbox_gamepad & pad)
	{
		//create vibration state
		XINPUT_VIBRATION vib_state;
		
		//assert 0 mem
		ZeroMemory(&vib_state, sizeof(XINPUT_VIBRATION));
		
		//set vibration speed
		vib_state.wLeftMotorSpeed = left_speed;
		vib_state.wRightMotorSpeed = right_speed;
		
		//set vibration state
		XInputSetState(pad.pad_index, &vib_state);
	}

	/** Sets the vibration speed for a @param pad with a single int value @param speed.*/
	void vibrate(int speed, altertum::xbox_gamepad & pad)
	{
		//create vibration state
		XINPUT_VIBRATION vib_state;
		
		//assert 0 mem
		ZeroMemory(&vib_state, sizeof(XINPUT_VIBRATION));
		
		//set vibration speed
		vib_state.wLeftMotorSpeed = speed;
		vib_state.wRightMotorSpeed = speed;
		
		//set vibration state
		XInputSetState(pad.pad_index, &vib_state);
	}
	void update(altertum::xbox_gamepad & pad)
	{
		//reset the pad state
		pad.state.reset();

		//update trigger states
		if (pad.xstate.Gamepad.bRightTrigger &&
			pad.xstate.Gamepad.bRightTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			pad.state.right_trigger = pad.xstate.Gamepad.bRightTrigger / 255.0f;
		}
		if (pad.xstate.Gamepad.bLeftTrigger &&
			pad.xstate.Gamepad.bLeftTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			pad.state.left_trigger = pad.xstate.Gamepad.bLeftTrigger / 255.0f;
		}

		//update button state
		if (pad.xstate.Gamepad.wButtons & XINPUT_GAMEPAD_A)//A
			pad.state.buttons[GP_BUTTON::A] = true;
		if (pad.xstate.Gamepad.wButtons & XINPUT_GAMEPAD_B)//B
			pad.state.buttons[GP_BUTTON::B] = true;
		if (pad.xstate.Gamepad.wButtons & XINPUT_GAMEPAD_X)//X
			pad.state.buttons[GP_BUTTON::X] = true;
		if (pad.xstate.Gamepad.wButtons & XINPUT_GAMEPAD_Y)//Y
			pad.state.buttons[GP_BUTTON::Y] = true;
		if (pad.xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)//D UP
			pad.state.buttons[GP_BUTTON::DPAD_UP] = true;
		if (pad.xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)//D DOWN
			pad.state.buttons[GP_BUTTON::DPAD_DOWN] = true;
		if (pad.xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)//D LEFT
			pad.state.buttons[GP_BUTTON::DPAD_LEFT] = true;
		if (pad.xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)//D RIGHT
			pad.state.buttons[GP_BUTTON::DPAD_RIGHT] = true;
		if (pad.xstate.Gamepad.wButtons & XINPUT_GAMEPAD_START)//START
			pad.state.buttons[GP_BUTTON::START] = true;
		if (pad.xstate.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)//BACK
			pad.state.buttons[GP_BUTTON::BACK] = true;
		if (pad.xstate.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)//L BUMPER
			pad.state.buttons[GP_BUTTON::L_BUMPER] = true;
		if (pad.xstate.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)//R BUMPER
			pad.state.buttons[GP_BUTTON::R_BUMPER] = true;
		if (pad.xstate.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)//L THUMB CLICK
			pad.state.buttons[GP_BUTTON::L_THUMB] = true;
		if (pad.xstate.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)//R THUMB CLICK
			pad.state.buttons[GP_BUTTON::R_THUMB] = true;

		//update stick states, if sticks are in deadzone, x and y values are 0
		//left stick
		if ((pad.xstate.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			pad.xstate.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
			(pad.xstate.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				pad.xstate.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
		{
			pad.xstate.Gamepad.sThumbLX = 0;
			pad.xstate.Gamepad.sThumbLY = 0;
		}

		//right stick
		if ((pad.xstate.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			pad.xstate.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
			(pad.xstate.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
				pad.xstate.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
		{
			pad.xstate.Gamepad.sThumbRX = 0;
			pad.xstate.Gamepad.sThumbRY = 0;
		}
		
		//store stick values in pad.state
		float left_thumb_x = pad.xstate.Gamepad.sThumbLX;
		float left_thumb_y = pad.xstate.Gamepad.sThumbLY;
		float right_thumb_x = pad.xstate.Gamepad.sThumbRX;
		float right_thumb_y = pad.xstate.Gamepad.sThumbRY;

		if (left_thumb_x)
		{
			pad.state.lstick_xy.x = left_thumb_x;
		}
		if (left_thumb_y)
		{
			pad.state.lstick_xy.y = left_thumb_y;
		}
		if (right_thumb_x)
		{
			pad.state.rstick_xy.x = right_thumb_x;
		}
		if (right_thumb_y)
		{
			pad.state.rstick_xy.y = right_thumb_y;
		}
	}
};//namespace gamepad
};//namespace altertum