/*
 * DefaultUndoRedoManagerTest.h
 *
 *  Created on: 04.11.2016
 *      Author: Gerd
 */

#ifndef INCLUDE_UNDOREDOMANAGERDELEGATIONTEST_H_
#define INCLUDE_UNDOREDOMANAGERDELEGATIONTEST_H_

#include <memory>

#include <UndoRedoFramework/ByDelegation/UndoRedoManagerImpl.h>
#include "UndoRedoManagerTest.h"

class UndoRedoManagerByDelegationTest :
		public UndoRedoManagerTest<UndoRedoFramework::ByDelegation::UndoRedoManager> {
public:
	using base_type = UndoRedoManagerTest<UndoRedoFramework::ByDelegation::UndoRedoManager>;
	using base_type::SUT;
	using UndoRedoManagerImpl = UndoRedoFramework::ByDelegation::UndoRedoManagerImpl;


	virtual std::unique_ptr<SUT> createSUT() const override {
		return std::unique_ptr<SUT>(
				new UndoRedoManagerImpl
		);
	}
	static cute::suite make_suite();
};
inline
cute::suite UndoRedoManagerByDelegationTest::make_suite(){
	cute::suite s { };
	UndoRedoManagerTests(UndoRedoManagerByDelegationTest)
	return s;
}



#endif /* INCLUDE_UNDOREDOMANAGERDELEGATIONTEST_H_ */
