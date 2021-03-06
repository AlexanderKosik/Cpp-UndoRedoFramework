/*
 * UndoRedoStackTest.h
 *
 *  Created on: 30.10.2016
 *      Author: Gerd
 */

#ifndef UNDOREDOSTACKTEST_H_
#define UNDOREDOSTACKTEST_H_

#include "cute.h"

#include "UndoRedoTest.h"

template<class SUTType>
class UndoRedoStackTest : public UndoRedoTest<SUTType> {

public:
	using base_type = UndoRedoTest<SUTType>;

	using typename base_type::SUT;

	using UndoRedoTest<SUT>::getSUT;
	using UndoRedoTest<SUT>::plus;
	using UndoRedoTest<SUT>::plusValue;
	using UndoRedoTest<SUT>::minus;
	using UndoRedoTest<SUT>::minusValue;
	using UndoRedoTest<SUT>::calculator;

	void DoIt();
	void DoItWithException();
	void DoItExceptionNeutral();

	void Undo();
	void UndoWithException();
	void UndoExceptionNeutral();

	void Redo();
	void RedoWithException();
	void RedoExceptionNeutral();

	void IsUndoable();
	void IsRedoable();

//	static cute::suite make_suite();
};
#define UndoRedoStackTests(DerivedTest)									\
		s.push_back(CUTE_SMEMFUN(DerivedTest, DoIt));					\
		s.push_back(CUTE_SMEMFUN(DerivedTest, DoItWithException));		\
		s.push_back(CUTE_SMEMFUN(DerivedTest, DoItExceptionNeutral));	\
		s.push_back(CUTE_SMEMFUN(DerivedTest, Undo));					\
		s.push_back(CUTE_SMEMFUN(DerivedTest, UndoWithException));		\
		s.push_back(CUTE_SMEMFUN(DerivedTest, UndoExceptionNeutral));	\
		s.push_back(CUTE_SMEMFUN(DerivedTest, Redo));					\
		s.push_back(CUTE_SMEMFUN(DerivedTest, RedoWithException));		\
		s.push_back(CUTE_SMEMFUN(DerivedTest, RedoExceptionNeutral));	\
		s.push_back(CUTE_SMEMFUN(DerivedTest, IsUndoable));				\
		s.push_back(CUTE_SMEMFUN(DerivedTest, IsRedoable));

template<class SUTType>
void UndoRedoStackTest<SUTType>::IsUndoable(){
	auto& urMngr(this->getSUT());

	urMngr.doIt(plus);
	ASSERT_EQUAL(true, urMngr.isUndoable());
}

template<class SUTType>
void UndoRedoStackTest<SUTType>::IsRedoable(){
	SUT& urMngr(getSUT());

	urMngr.doIt(plus);
	urMngr.undo();
	ASSERT_EQUAL(true, urMngr.isRedoable());
}

template<class SUTType>
void UndoRedoStackTest<SUTType>::DoIt(){
	SUT& urMngr(getSUT());

	Plus::throwException() = false;

	urMngr.doIt(Plus(calculator, plusValue));

	int expected = plusValue;
	int result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(true, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}
template<class SUTType>
void UndoRedoStackTest<SUTType>::Undo(){
	SUT& urMngr(getSUT());

	Plus::throwException() = false;
	urMngr.doIt(plus);
	urMngr.undo();

	int result = calculator.getResult();
	int expected { 0 };

	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(true, urMngr.isRedoable());
}
template<class SUTType>
void UndoRedoStackTest<SUTType>::Redo(){
	SUT& urMngr(getSUT());

	Plus::throwException() = false;
	urMngr.doIt(plus);
	urMngr.undo();

	urMngr.redo();

	int expected = plusValue;
	int result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(true, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}
template<class SUTType>
void UndoRedoStackTest<SUTType>::DoItWithException(){
	SUT& urMngr(getSUT());

	Plus::throwException() = true;
	int result = calculator.getResult();
	int expected = 0;
	ASSERT_EQUAL(expected, result);

	try{
		urMngr.doIt(plus);
	}catch(...){}

	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}

template<class SUTType>
void UndoRedoStackTest<SUTType>::UndoWithException(){
	SUT& urMngr(getSUT());

	urMngr.doIt(plus);

	int expected = plusValue;
	int result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	Plus::throwException() = true;

	try{
		urMngr.undo();
	}catch(...){
//		cout << "catch UndoWithException" << endl;
	}

	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(true, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}

template<class SUTType>
void UndoRedoStackTest<SUTType>::RedoWithException(){
	SUT& urMngr(getSUT());

	Plus::throwException() = false;
	urMngr.doIt(plus);
	urMngr.undo();
	Plus::throwException() = true;
	try{
		urMngr.redo();
	}catch(...){
//		cout << "catch RedoWithException" << endl;
	}

	int result = calculator.getResult();
	int expected { 0 };
	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(true, urMngr.isRedoable());
}

template<class SUTType>
void UndoRedoStackTest<SUTType>::DoItExceptionNeutral(){
	SUT& urMngr(getSUT());

	Plus::throwException() = true;

	ASSERT_THROWS(urMngr.doIt(plus), std::logic_error);
}
//==========
template<class SUTType>
void UndoRedoStackTest<SUTType>::UndoExceptionNeutral(){
	SUT& urMngr(getSUT());

	Plus::throwException() = false;
	urMngr.doIt(plus);
	Plus::throwException() = true;

	ASSERT_THROWS(urMngr.undo(), std::logic_error);
}
//==========
template<class SUTType>
void UndoRedoStackTest<SUTType>::RedoExceptionNeutral(){
	SUT& urMngr(getSUT());

	Plus::throwException() = false;
	urMngr.doIt(plus);
	urMngr.undo();
	Plus::throwException() = true;

	ASSERT_THROWS(urMngr.redo(), std::logic_error);
}


#endif /* UNDOREDOSTACKTEST_H_ */
