// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAITHREAD_H
#define	MOAITHREAD_H

#include <moaicore/MOAIAction.h>

//================================================================//
// MOAIThread
//================================================================//
/**	@brief Thread class.
*/
class MOAIThread :
	public MOAIAction {
private:

	USLuaRef		mRef;
	lua_State*		mState;
	u32				mNarg;
	
	//----------------------------------------------------------------//
	static int		_blockOnAction			( lua_State* L );
	static int		_currentThread			( lua_State* L );
	static int		_run					( lua_State* L );
	
	//----------------------------------------------------------------//
	
public:
	
	DECL_LUA_DATA ( MOAIThread )
	
	//----------------------------------------------------------------//						
					MOAIThread				();
					~MOAIThread				();
	bool			IsBusy					();
	void			OnUpdate				( float step );
	void			RegisterLuaClass		( USLuaState& state );
	void			RegisterLuaFuncs		( USLuaState& state );
};

#endif