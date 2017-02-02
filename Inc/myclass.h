#ifndef MYCLASS_H_
#define MYCLASS_H_

#ifdef __cplusplus
 extern "C" {
#endif

class MyClass
{
	public:
		MyClass ();
		int incby(int v, int inc);
};

#ifdef __cplusplus
}
#endif

#endif /* MYCLASS_H_ */
