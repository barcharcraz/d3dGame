#include "stdafx.h"
#include "HLSLCache.h"
#include <LibEffects/EffectsManagement.h>
#include <unordered_map>
#include <iostream>
namespace Effects {
	namespace {
		std::unordered_map<std::string, HLSLPixelShader> psmap;
		std::unordered_map<std::string, HLSLVertexShader> vsmap;
		ID3D11Device* lastDevice;
		void WarnDeviceChange() {
			std::cerr << "WARNING: getting shader from a new device"
				"and flushing shader cache";
		}
		void flush_cache() {
			psmap.clear();
			vsmap.clear();
		}
	}
	HLSLPixelShader* GetHLSLPixelShader(ID3D11Device* pDev, const std::string& name) {
		if (pDev != lastDevice) {
			WarnDeviceChange();
			flush_cache();
			lastDevice = pDev;
		}
		auto iter = psmap.find(name);
		if (iter == psmap.end()) {
			return &psmap.emplace(name, HLSLPixelShader{ name }).first->second;
		} else {
			return &iter->second;
		}
	}
	HLSLVertexShader* GetHLSLVertexShader(ID3D11Device* pDev, const std::string& name, const std::vector<ShaderDesc>& desc) {
		if (pDev != lastDevice) {
			WarnDeviceChange();
			flush_cache();
			lastDevice = pDev;
		}
		auto iter = vsmap.find(name);
		if (iter == vsmap.end()) {
			return &vsmap.emplace(name, HLSLVertexShader{ name, desc }).first->second;
		} else {
			return &iter->second;
		}
	}
}