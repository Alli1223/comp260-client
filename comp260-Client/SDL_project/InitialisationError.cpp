#include "stdafx.h"
#include "InitialisationError.h"


InitialisationError::InitialisationError(const std::string& msg)
{
	message = msg + "\n" + SDL_GetError();
}
