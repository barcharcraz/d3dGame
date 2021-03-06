#include "Effect.h"

namespace Effects {
	Effect::Effect(const std::string& vsfile, const std::string& psfile, 
		const std::vector<ShaderDesc>& desc,
		const std::set<ShaderCaps>& scaps)
		: caps(scaps), vs(vsfile, desc), ps(psfile)
	{

	}
}
