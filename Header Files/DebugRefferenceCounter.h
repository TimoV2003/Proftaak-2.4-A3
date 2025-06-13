#pragma once

namespace DebugRefferenceCounter {
	void IncrementObjectReferenceCounter();
	void DecrementObjectReferenceCounter();
	void IncrementComponentReferenceCounter();
	void DecrementComponentReferenceCounter();
	int GetObjectReferenceCounter();
	int GetComponentReferenceCounter();
}
