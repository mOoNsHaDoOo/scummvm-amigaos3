/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef COMMON_CALLBACK_H
#define COMMON_CALLBACK_H

namespace Common {

/**
 * BaseCallback<S> is a simple base class for object-oriented callbacks.
 *
 * Object-oriented callbacks are such callbacks that know exact instance
 * which method must be called.
 *
 * For backwards compatibility purposes, there is a GlobalFunctionCallback,
 * which is BaseCallback<void *>, so it can be used with global C-like
 * functions too.
 *
 * <S> is the type, which is passed to operator() of this callback.
 * This allows you to specify that you accept a callback, which wants
 * to receive an <S> object.
 */
template<typename S = void *> class BaseCallback {
public:
	BaseCallback() {}
	virtual ~BaseCallback() {}
	virtual void operator()(S data) = 0;
};

/**
 * GlobalFunctionCallback<T> is a simple wrapper for global C functions.
 *
 * If there is a method, which accepts BaseCallback<T>, you can
 * easily pass your C function by passing
 *     new GlobalFunctionCallback<T>(yourFunction)
 */
template<typename T> class GlobalFunctionCallback: public BaseCallback<T> {
	typedef void(*GlobalFunction)(T result);
	GlobalFunction _callback;

public:
	GlobalFunctionCallback(GlobalFunction cb): _callback(cb) {}
	virtual ~GlobalFunctionCallback() {}
	virtual void operator()(T data) {
		if (_callback) _callback(data);
	}
};

/**
 * Callback<T, S> implements an object-oriented callback.
 *
 * <T> stands for a class which method you want to call.
 * <S>, again, is the type of an object passed to operator().
 *
 * So, if you have void MyClass::myMethod(AnotherClass) method,
 * the corresponding callback is Callback<MyClass, AnotherClass>.
 * You create it similarly to this:
 *     new Callback<MyClass, AnotherClass>(
 *         pointerToMyClassObject,
 *         &MyClass::myMethod
 *     )
 */
template<class T, typename S = void *> class Callback: public BaseCallback<S> {
protected:
	typedef void(T::*TMethod)(S);
	T *_object;
	TMethod _method;
public:
	Callback(T *object, TMethod method): _object(object), _method(method) {}
	virtual ~Callback() {}
	void operator()(S data) { (_object->*_method)(data); }
};

/**
 * CallbackBridge<T, OS, S> helps you to chain callbacks.
 *
 * CallbackBridge keeps a pointer to BaseCallback<OS>.
 * When its operator() is called, it passes this pointer
 * along with the actual data (of type <S>) to the method
 * of <T> class.
 *
 * This is needed when you have to call a callback only
 * when your own callback is called. So, your callback
 * is "inner" and the other one is "outer".
 *
 * CallbackBridge implements the "inner" one and calls
 * the method you wanted. It passes the "outer", so you
 * can call it from your method. You can ignore it, but
 * probably there is no point in using CallbackBridge then.
 *
 * So, if you receive a BaseCallback<SomeClass> callback
 * and you want to call it from your MyClass::myMethod method,
 * you should create CallbackBridge<MyClass, SomeClass, S>,
 * where <S> is data type you want to receive in MyClass::myMethod.
 *
 * You create it similarly to this:
 *     new Callback<MyClass, SomeClass, AnotherClass>(
 *         pointerToMyClassObject,
 *         &MyClass::myMethod,
 *         outerCallback
 *     )
 * where `outerCallback` is BaseCallback<SomeClass> and `myMethod` is:
 * void MyClass::myMethod(BaseCallback<SomeClass>  *, AnotherClass)
 */
template<class T, typename OS, typename S = void *> class CallbackBridge: public BaseCallback<S> {
	typedef void(T::*TCallbackMethod)(BaseCallback<OS> *, S);
	T *_object;
	TCallbackMethod _method;
	BaseCallback<OS> *_outerCallback;
public:
	CallbackBridge(T *object, TCallbackMethod method, BaseCallback<OS> *outerCallback):
		_object(object), _method(method), _outerCallback(outerCallback) {}
	virtual ~CallbackBridge() {}
	void operator()(S data) { (_object->*_method)(_outerCallback, data); }
};

} // End of namespace Common

#endif
