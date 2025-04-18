#include <jni.h>

#include "mdName.h"

class Utf8String {
	private:
		JNIEnv* env;
		const char* utf8Ptr;
		jstring jString;
	public:
		Utf8String(JNIEnv* jEnv,jstring str);
		~Utf8String();
		const char* GetUtf8Ptr();
};

Utf8String::Utf8String(JNIEnv* jEnv,jstring str) {
	env=jEnv;
	jString=str;
	if (jString!=0)
		utf8Ptr=env->GetStringUTFChars(jString,0);
	else
		utf8Ptr=0;
}

Utf8String::~Utf8String() {
	if (utf8Ptr!=0)
		env->ReleaseStringUTFChars(jString,utf8Ptr);
}

const char* Utf8String::GetUtf8Ptr() {
	if (utf8Ptr!=0)
		return utf8Ptr;
	return "";
}

jstring UnicodeString(JNIEnv* jEnv,const char* str) {
	if (str!=0)
		return jEnv->NewStringUTF(str);
	return jEnv->NewStringUTF("");
}

extern "C" JNIEXPORT jlong JNICALL Java_com_melissadata_mdNameJNI_mdNameCreate(JNIEnv* /*jEnv*/,jclass /*jCls*/) {
	return (jlong) new mdName();
}

extern "C" JNIEXPORT void JNICALL Java_com_melissadata_mdNameJNI_mdNameDestroy(JNIEnv* /*jEnv*/,jclass /*jCls*/,jlong I) {
	delete (mdName*) I;
}

extern "C" JNIEXPORT void JNICALL Java_com_melissadata_mdNameJNI_SetPathToNameFiles(JNIEnv* jEnv,jclass /*jCls*/,jlong I,jstring p1) {
	Utf8String _p1(jEnv,p1);
	((mdName*) I)->SetPathToNameFiles(_p1.GetUtf8Ptr());
}

extern "C" JNIEXPORT jint JNICALL Java_com_melissadata_mdNameJNI_InitializeDataFiles(JNIEnv* /*jEnv*/,jclass /*jCls*/,jlong I) {
	return (jint) ((mdName*) I)->InitializeDataFiles();
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetInitializeErrorString(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetInitializeErrorString());
}

extern "C" JNIEXPORT jint JNICALL Java_com_melissadata_mdNameJNI_SetLicenseString(JNIEnv* jEnv,jclass /*jCls*/,jlong I,jstring p1) {
	Utf8String _p1(jEnv,p1);
	return (jint) ((mdName*) I)->SetLicenseString(_p1.GetUtf8Ptr());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetBuildNumber(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetBuildNumber());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetDatabaseDate(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetDatabaseDate());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetDatabaseExpirationDate(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetDatabaseExpirationDate());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetLicenseExpirationDate(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetLicenseExpirationDate());
}

extern "C" JNIEXPORT jint JNICALL Java_com_melissadata_mdNameJNI_SetPrimaryNameHint(JNIEnv* /*jEnv*/,jclass /*jCls*/,jlong I,jint p1) {
	return (jint) ((mdName*) I)->SetPrimaryNameHint((mdName::NameHints) p1);
}

extern "C" JNIEXPORT jint JNICALL Java_com_melissadata_mdNameJNI_SetSecondaryNameHint(JNIEnv* /*jEnv*/,jclass /*jCls*/,jlong I,jint p1) {
	return (jint) ((mdName*) I)->SetSecondaryNameHint((mdName::NameHints) p1);
}

extern "C" JNIEXPORT jint JNICALL Java_com_melissadata_mdNameJNI_SetFirstNameSpellingCorrection(JNIEnv* /*jEnv*/,jclass /*jCls*/,jlong I,jint p1) {
	return (jint) ((mdName*) I)->SetFirstNameSpellingCorrection((int) p1);
}

extern "C" JNIEXPORT jint JNICALL Java_com_melissadata_mdNameJNI_SetMiddleNameLogic(JNIEnv* /*jEnv*/,jclass /*jCls*/,jlong I,jint p1) {
	return (jint) ((mdName*) I)->SetMiddleNameLogic((mdName::MiddleNameLogic) p1);
}

extern "C" JNIEXPORT jint JNICALL Java_com_melissadata_mdNameJNI_SetGenderPopulation(JNIEnv* /*jEnv*/,jclass /*jCls*/,jlong I,jint p1) {
	return (jint) ((mdName*) I)->SetGenderPopulation((mdName::Population) p1);
}

extern "C" JNIEXPORT jint JNICALL Java_com_melissadata_mdNameJNI_SetGenderAggression(JNIEnv* /*jEnv*/,jclass /*jCls*/,jlong I,jint p1) {
	return (jint) ((mdName*) I)->SetGenderAggression((mdName::Aggression) p1);
}

extern "C" JNIEXPORT jint JNICALL Java_com_melissadata_mdNameJNI_AddSalutation(JNIEnv* /*jEnv*/,jclass /*jCls*/,jlong I,jint p1) {
	return (jint) ((mdName*) I)->AddSalutation((mdName::Salutations) p1);
}

extern "C" JNIEXPORT void JNICALL Java_com_melissadata_mdNameJNI_SetSalutationPrefix(JNIEnv* jEnv,jclass /*jCls*/,jlong I,jstring p1) {
	Utf8String _p1(jEnv,p1);
	((mdName*) I)->SetSalutationPrefix(_p1.GetUtf8Ptr());
}

extern "C" JNIEXPORT void JNICALL Java_com_melissadata_mdNameJNI_SetSalutationSuffix(JNIEnv* jEnv,jclass /*jCls*/,jlong I,jstring p1) {
	Utf8String _p1(jEnv,p1);
	((mdName*) I)->SetSalutationSuffix(_p1.GetUtf8Ptr());
}

extern "C" JNIEXPORT void JNICALL Java_com_melissadata_mdNameJNI_SetSalutationSlug(JNIEnv* jEnv,jclass /*jCls*/,jlong I,jstring p1) {
	Utf8String _p1(jEnv,p1);
	((mdName*) I)->SetSalutationSlug(_p1.GetUtf8Ptr());
}

extern "C" JNIEXPORT void JNICALL Java_com_melissadata_mdNameJNI_ClearProperties(JNIEnv* /*jEnv*/,jclass /*jCls*/,jlong I) {
	((mdName*) I)->ClearProperties();
}

extern "C" JNIEXPORT void JNICALL Java_com_melissadata_mdNameJNI_SetFullName(JNIEnv* jEnv,jclass /*jCls*/,jlong I,jstring p1) {
	Utf8String _p1(jEnv,p1);
	((mdName*) I)->SetFullName(_p1.GetUtf8Ptr());
}

extern "C" JNIEXPORT void JNICALL Java_com_melissadata_mdNameJNI_SetPrefix(JNIEnv* jEnv,jclass /*jCls*/,jlong I,jstring p1) {
	Utf8String _p1(jEnv,p1);
	((mdName*) I)->SetPrefix(_p1.GetUtf8Ptr());
}

extern "C" JNIEXPORT void JNICALL Java_com_melissadata_mdNameJNI_SetPrefix2(JNIEnv* jEnv,jclass /*jCls*/,jlong I,jstring p1) {
	Utf8String _p1(jEnv,p1);
	((mdName*) I)->SetPrefix2(_p1.GetUtf8Ptr());
}

extern "C" JNIEXPORT void JNICALL Java_com_melissadata_mdNameJNI_SetFirstName(JNIEnv* jEnv,jclass /*jCls*/,jlong I,jstring p1) {
	Utf8String _p1(jEnv,p1);
	((mdName*) I)->SetFirstName(_p1.GetUtf8Ptr());
}

extern "C" JNIEXPORT void JNICALL Java_com_melissadata_mdNameJNI_SetFirstName2(JNIEnv* jEnv,jclass /*jCls*/,jlong I,jstring p1) {
	Utf8String _p1(jEnv,p1);
	((mdName*) I)->SetFirstName2(_p1.GetUtf8Ptr());
}

extern "C" JNIEXPORT void JNICALL Java_com_melissadata_mdNameJNI_SetMiddleName(JNIEnv* jEnv,jclass /*jCls*/,jlong I,jstring p1) {
	Utf8String _p1(jEnv,p1);
	((mdName*) I)->SetMiddleName(_p1.GetUtf8Ptr());
}

extern "C" JNIEXPORT void JNICALL Java_com_melissadata_mdNameJNI_SetMiddleName2(JNIEnv* jEnv,jclass /*jCls*/,jlong I,jstring p1) {
	Utf8String _p1(jEnv,p1);
	((mdName*) I)->SetMiddleName2(_p1.GetUtf8Ptr());
}

extern "C" JNIEXPORT void JNICALL Java_com_melissadata_mdNameJNI_SetSuffix(JNIEnv* jEnv,jclass /*jCls*/,jlong I,jstring p1) {
	Utf8String _p1(jEnv,p1);
	((mdName*) I)->SetSuffix(_p1.GetUtf8Ptr());
}

extern "C" JNIEXPORT void JNICALL Java_com_melissadata_mdNameJNI_SetSuffix2(JNIEnv* jEnv,jclass /*jCls*/,jlong I,jstring p1) {
	Utf8String _p1(jEnv,p1);
	((mdName*) I)->SetSuffix2(_p1.GetUtf8Ptr());
}

extern "C" JNIEXPORT void JNICALL Java_com_melissadata_mdNameJNI_SetLastName(JNIEnv* jEnv,jclass /*jCls*/,jlong I,jstring p1) {
	Utf8String _p1(jEnv,p1);
	((mdName*) I)->SetLastName(_p1.GetUtf8Ptr());
}

extern "C" JNIEXPORT void JNICALL Java_com_melissadata_mdNameJNI_SetLastName2(JNIEnv* jEnv,jclass /*jCls*/,jlong I,jstring p1) {
	Utf8String _p1(jEnv,p1);
	((mdName*) I)->SetLastName2(_p1.GetUtf8Ptr());
}

extern "C" JNIEXPORT jint JNICALL Java_com_melissadata_mdNameJNI_Parse(JNIEnv* /*jEnv*/,jclass /*jCls*/,jlong I) {
	return (jint) ((mdName*) I)->Parse();
}

extern "C" JNIEXPORT jint JNICALL Java_com_melissadata_mdNameJNI_Genderize(JNIEnv* /*jEnv*/,jclass /*jCls*/,jlong I) {
	return (jint) ((mdName*) I)->Genderize();
}

extern "C" JNIEXPORT jint JNICALL Java_com_melissadata_mdNameJNI_Salutate(JNIEnv* /*jEnv*/,jclass /*jCls*/,jlong I) {
	return (jint) ((mdName*) I)->Salutate();
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetStatusCode(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetStatusCode());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetErrorCode(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetErrorCode());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetChangeCode(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetChangeCode());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetResults(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetResults());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetResultCodeDescription(JNIEnv* jEnv,jclass /*jCls*/,jlong I,jstring p1,jint opt) {
	Utf8String _p1(jEnv,p1);
	return UnicodeString(jEnv,((mdName*) I)->GetResultCodeDescription(_p1.GetUtf8Ptr(),(mdName::ResultCdDescOpt) opt));
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetPrefix(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetPrefix());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetPrefix2(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetPrefix2());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetFirstName(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetFirstName());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetFirstName2(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetFirstName2());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetMiddleName(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetMiddleName());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetMiddleName2(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetMiddleName2());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetLastName(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetLastName());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetLastName2(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetLastName2());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetSuffix(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetSuffix());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetSuffix2(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetSuffix2());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetGender(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetGender());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetGender2(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetGender2());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetSalutation(JNIEnv* jEnv,jclass /*jCls*/,jlong I) {
	return UnicodeString(jEnv,((mdName*) I)->GetSalutation());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_StandardizeCompany(JNIEnv* jEnv,jclass /*jCls*/,jlong I,jstring p1) {
	Utf8String _p1(jEnv,p1);
	return UnicodeString(jEnv,((mdName*) I)->StandardizeCompany(_p1.GetUtf8Ptr()));
}

extern "C" JNIEXPORT void JNICALL Java_com_melissadata_mdNameJNI_SetReserved(JNIEnv* jEnv,jclass /*jCls*/,jlong I,jstring p1,jstring p2) {
	Utf8String _p1(jEnv,p1);
	Utf8String _p2(jEnv,p2);
	((mdName*) I)->SetReserved(_p1.GetUtf8Ptr(),_p2.GetUtf8Ptr());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_melissadata_mdNameJNI_GetReserved(JNIEnv* jEnv,jclass /*jCls*/,jlong I,jstring p1) {
	Utf8String _p1(jEnv,p1);
	return UnicodeString(jEnv,((mdName*) I)->GetReserved(_p1.GetUtf8Ptr()));
}

