//
//  kern_start.cpp
//  NoTouchID
//
//  Copyright (C) 2018 Alex James (TheRacerMaster). All rights reserved.
//

#include <Library/LegacyIOService.h>
#include <Headers/plugin_start.hpp>
#include <Headers/kern_api.hpp>

// Target framework
static const char binPath[] = "/System/Library/PrivateFrameworks/BiometricKit.framework/Versions/A/BiometricKit";

// Accompanied processes
static const char procPath[] = "/System/Library/Frameworks/LocalAuthentication.framework/Support/DaemonUtils.framework/Versions/A/DaemonUtils";

static const uint8_t find[] = "board-id";
static const uint8_t repl[] = "board-ix";

static_assert(sizeof(find) == sizeof(repl), "Invalid patch size");

static UserPatcher::BinaryModPatch patch {
	CPU_TYPE_X86_64,
	0,
	find,
	repl,
	sizeof(find) - 1,
	0,
	1,
	UserPatcher::FileSegment::SegmentTextCstring,
	1
};

UserPatcher::BinaryModInfo ADDPR(binaryMod)[] {
	{ binPath, &patch, 1 }
};

const size_t ADDPR(binaryModSize) = 1;

static UserPatcher::ProcInfo ADDPR(procInfo)[] {
	{ procPath, sizeof(procPath) - 1, 1 }
};

const size_t ADDPR(procInfoSize) = 1;

static const char *bootargOff[] {
	"-nobiooff"
};

static const char *bootargBeta[] {
	"-nobiobeta"
};

PluginConfiguration ADDPR(config) {
	xStringify(PRODUCT_NAME),
	parseModuleVersion(xStringify(MODULE_VERSION)),
	LiluAPI::AllowNormal,
	bootargOff,
	arrsize(bootargOff),
	nullptr,
	0,
	bootargBeta,
	arrsize(bootargBeta),
	KernelVersion::HighSierra,
	KernelVersion::Catalina,
	[]() {
		lilu.onProcLoad(ADDPR(procInfo), ADDPR(procInfoSize), nullptr, nullptr, ADDPR(binaryMod), ADDPR(binaryModSize));
	}
};
