#include "_Core.h"
#include "RenderCommand.h"

namespace core
{
	Shr<RenderAPI> RenderCommand::rendererAPI = RenderAPI::CreateAPI();
}
