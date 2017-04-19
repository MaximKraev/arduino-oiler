//  Callback.h

#ifndef CALLBACK_H
#define CALLBACK_H

template <class T>
class cCallback
{
	public:
		virtual bool Execute(T Param) const = 0;
};

template <class T>
class TCallback : public cCallback<T> // Inheriting
{
	public:
		TCallback() // constructor
		{
			// Important : zeroing the pointer so we later can check for errors
			pFunction = 0;
		}

		// (You can change the callback to take more parameters or to return something)
		typedef bool (*tFunction)(T param);

		// Execute the Callback
		virtual bool Execute(T Param) const
		{
			if (pFunction) return (*pFunction)(Param);
			else printf("ERROR : the callback function has not been defined !!!!");
			// an undefined callback function will crash the program if you don't check here !
			return false;
		}

		// Set or change the Callback
		void SetCallback (tFunction pFunctionPointer)
		{
			pFunction = pFunctionPointer;
		}

	private:
		tFunction  pFunction;
};

#define cCallbackFloat cCallback<float>
#define TCallbackFloat TCallback<float>

#define cCallbackBool cCallback<bool>
#define TCallbackBool TCallback<bool>

#define cCallbackVoid cCallback<void>
#define TCallbackVoid TCallback<void>

#endif // CALLBACK_H



