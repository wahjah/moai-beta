// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAILOGMESSAGES_H
#define	MOAILOGMESSAGES_H

#include <moaicore/MOAILogMgr.h>

#define REGISTER_LOG_MESSAGE(messageID) state.SetField ( -1, #messageID, ( u32 )messageID );

#ifdef _DEBUG
	#define MOAI_LUA_SETUP(type,str)									\
		USLuaState state ( L );											\
		if ( !state.CheckParams ( 1, str )) {							\
			MOAILog ( L, MOAILogMessages::MOAI_ParamTypeMismatch );		\
			return 0;													\
		}																\
		type* self = state.GetLuaObject < type >( 1 );					\
		if ( !self ) return 0;
#else
	#define MOAI_LUA_SETUP(type,str)									\
		USLuaState state ( L );											\
		type* self = state.GetLuaObject < type >( 1 );					\
		if ( !self ) return 0;
#endif

//================================================================//
// MOAILogMessages
//================================================================//
class MOAILogMessages {
public:

	enum {
		MOAI_FileNotFound_S,
		MOAI_IndexNoReserved,
		MOAI_IndexOutOfRange_DDD,
		MOAI_NewIsUnsupported,
		MOAI_ParamTypeMismatch,
		MOAIAction_Profile_PSFF,
		MOAIBox2DBody_MissingInstance,
		MOAIBox2DFixture_MissingInstance,
		MOAIGfxDevice_OpenGLError_S,
		MOAINode_AttributeNotFound,
		MOAIShader_ShaderInfoLog_S,
		MOAITexture_MemoryUse_SDFS,
		MOAITexture_MissingDevice_S,
		MOAITexture_NoFramebuffer,
		MOAITexture_NonPowerOfTwo_SDD,
	};
	
	//----------------------------------------------------------------//
	static int		_alertNewIsUnsupported			( lua_State* L );

	//----------------------------------------------------------------//
	static bool		CheckFileExists					( cc8* filename, lua_State* L = 0 );
	static bool		CheckIndex						( u32 idx, u32 size, lua_State* L = 0 );
	static bool		CheckIndexPlusOne				( u32 idx, u32 size, lua_State* L = 0 );
	static bool		CheckReserve					( u32 idx, u32 size, lua_State* L = 0 );
	static void		RegisterDefaultLogMessages		();
	static void		RegisterLogMessageIDs			( USLuaState& state );
};

#endif
