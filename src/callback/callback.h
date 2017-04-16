//  Callback.h

#ifndef CALLBACK_H
#define CALLBACK_H


class cCallback
{
	public:
		virtual bool Execute(void *Param) const =0;
};

class TCallback : public cCallback // Inheriting
{
	public:
		TCallback() // constructor
		{
			// Important : zeroing the pointer so we later can check for errors
			pFunction = 0;
		}

		// (You can change the callback to take more parameters or to return something)
		typedef bool (*tFunction)(void *Param);

		// Execute the Callback
		virtual bool Execute(void *Param) const
		{
			if (pFunction) return (*pFunction)(Param);
			else printf("ERROR : the callback function has not been defined !!!!");
			// an undefined callback function will crash the program if you don't check here !
			return false;
		}

		// Set or change the Callback
		void SetCallback (tFunction   pFunctionPointer)
		{
			pFunction = pFunctionPointer;
		}

	private:
		tFunction  pFunction;
};

#endif // CALLBACK_H



