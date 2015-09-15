/*
 * Copyright (C) 2015 Sergey Kosarevsky (sk@linderdaum.com)
 * Copyright (C) 2015 Viktor Latypov (vl@linderdaum.com)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must display the names 'Sergey Kosarevsky' and
 *    'Viktor Latypov'in the credits of the application, if such credits exist.
 *    The authors of this work must be notified via email (sk@linderdaum.com) in
 *    this case of redistribution.
 *
 * 3. Neither the name of copyright holders nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
#include <string>

#include "Callbacks.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "NDKApp", __VA_ARGS__))

std::string g_APKName;

std::string ConvertJString( JNIEnv* env, jstring str )
{
	if ( !str ) { return std::string(); }

	const jsize len = env->GetStringUTFLength( str );
	const char* strChars = env->GetStringUTFChars( str, ( jboolean* )0 );

	std::string Result( strChars, len );

	env->ReleaseStringUTFChars( str, strChars );

	return Result;
}

extern "C"
{
	JNIEXPORT void JNICALL Java_com_packtpub_ndkmastering_AppActivity_onCreateNative( JNIEnv* env, jobject obj, jstring APKName )
	{
		g_APKName = ConvertJString( env, APKName );

		LOGI( "APKName = %s", g_APKName.c_str() );

		OnStart( g_APKName );
	}
}