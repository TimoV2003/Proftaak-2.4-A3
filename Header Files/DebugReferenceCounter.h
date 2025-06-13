#pragma once

namespace DebugReferenceCounter {
	void IncrementObjectReferenceCounter();
	void DecrementObjectReferenceCounter();
	void IncrementComponentReferenceCounter();
	void DecrementComponentReferenceCounter();
	int GetObjectReferenceCounter();
	int GetComponentReferenceCounter();
}
