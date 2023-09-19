/*
	File:  MTProfessionalVideoWorkflow.h
 
	Framework:  MediaToolbox
 
	Copyright © 2014 Apple Inc. All rights reserved.

	To report bugs, go to:  http://developer.apple.com/bugreporter/
*/


#ifndef MTPROFESSIONALVIDEOWORKFLOW_H
#define MTPROFESSIONALVIDEOWORKFLOW_H

#include <CoreMedia/CMBase.h>
#if !TARGET_OS_IPHONE

#if defined(__cplusplus)
extern "C"
{
#endif

#pragma pack(push, 4)

/*!
	@function	MTRegisterProfessionalVideoWorkflowFormatReaders
	@abstract	Allows the client to use file format readers appropriate for professional video workflows.
	@discussion	By convention, format readers registered using this function should conform to the abstract UTType of "com.apple.mediaextension-content" which in turn conforms to the abstract type "public.movie". Applications calling this function can use the type "com.apple.mediaextension-content" to do type filtering (e.g. in Open... dialogs).
*/
MT_EXPORT void MTRegisterProfessionalVideoWorkflowFormatReaders( void )  __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_NA);

#pragma pack(pop)

#if defined(__cplusplus)
}
#endif

#endif // !TARGET_OS_IPHONE

#endif // MTPROFESSIONALVIDEOWORKFLOW_H
