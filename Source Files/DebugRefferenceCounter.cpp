#include "DebugRefferenceCounter.h"

namespace DebugRefferenceCounter {
	static int objectReferenceCounter = 0;
	static int componentReferenceCounter = 0;

	void IncrementObjectReferenceCounter() {
		objectReferenceCounter++;
	}

	void DecrementObjectReferenceCounter() {
		objectReferenceCounter--;
	}


	void IncrementComponentReferenceCounter() {
		componentReferenceCounter++;
	}

	void DecrementComponentReferenceCounter() {
		componentReferenceCounter--;
	}

	int GetObjectReferenceCounter() {
		return objectReferenceCounter;
	}

	int GetComponentReferenceCounter() {
		return componentReferenceCounter;
	}
}