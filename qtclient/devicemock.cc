#include "devicemock.h"
#include "keyboardcomm.h"

int DeviceSessionMock::deviceSessionID = 0;
int DeviceMock::deviceID = 0;


static const unsigned char kinesis_default_mapping[172] = {
	0xfe, 0xfd, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
	0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11,
	0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
	0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21,
	0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x3a, 0x3b,
	0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43,
	0x44, 0x45, 0x2e, 0x2b, 0x29, 0x39, 0xe1, 0x52,
	0x51, 0x50, 0x4f, 0x2f, 0x30, 0x47, 0x46, 0x64,
	0x35, 0x2d, 0x48, 0x4d, 0x4a, 0x4c, 0x2a, 0xe2,
	0xe0, 0x31, 0x4e, 0x4b, 0x28, 0x2c, 0xe6, 0xe4,
	0x33, 0x34, 0x36, 0x37, 0x38, 0xe5, 0xfe, 0xfd,
	0x04, 0x05, 0x06, 0xee, 0xed, 0xf0, 0x0a, 0x0b,
	0x60, 0x5c, 0x5d, 0x5e, 0x59, 0x11, 0x61, 0x56,
	0x14, 0x15, 0xef, 0x17, 0x5f, 0x19, 0x1a, 0x1b,
	0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23,
	0x53, 0x2e, 0x54, 0x55, 0x3a, 0x3b, 0x3c, 0x3d,
	0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45,
	0x2e, 0x2b, 0x29, 0xff, 0xe1, 0x52, 0x51, 0x50,
	0x4f, 0x63, 0x58, 0xe7, 0xe3, 0x49, 0x35, 0x2d,
	0x65, 0xec, 0xeb, 0xe9, 0xe8, 0xe2, 0xea, 0x31,
	0x4e, 0x4b, 0x28, 0x62, 0xe6, 0xe4, 0x57, 0x34,
	0x5a, 0x5b, 0x58, 0xe5
};


static const unsigned char ergodox_default_mapping[152] = {
	0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,
	0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13,
	0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b,
	0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23,
	0x24, 0x25, 0x26, 0x27, 0x33, 0x36, 0x37, 0x38,
	0x2e, 0x2b, 0x39, 0xe1, 0xe3, 0x35, 0x64, 0x50,
	0x4f, 0xfd, 0xfc, 0xff, 0x2d, 0x31, 0x34, 0xe5,
	0xe7, 0x30, 0x2f, 0x51, 0x52, 0xfe, 0xfc, 0xff,
	0xe2, 0xe0, 0x4a, 0x4d, 0x2a, 0x4c, 0xe6, 0xe4,
	0x4b, 0x4e, 0x28, 0x2c, 0x04, 0x05, 0x06, 0xee,
	0xed, 0xf0, 0x0a, 0x0b, 0x60, 0x5c, 0x5d, 0x5e,
	0x59, 0x11, 0x61, 0x56, 0x14, 0x15, 0xef, 0x17,
	0x5f, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
	0x20, 0x21, 0x22, 0x23, 0x53, 0x2e, 0x54, 0x55,
	0x33, 0x36, 0x37, 0x38, 0x2e, 0x2b, 0x39, 0xe1,
	0xe3, 0x35, 0x64, 0x50, 0x4f, 0xfd, 0xfc, 0xff,
	0x2d, 0x31, 0x34, 0xe5, 0xe7, 0x58, 0x63, 0x51,
	0x52, 0xfe, 0xfc, 0xff, 0xe2, 0xea, 0xeb, 0xec,
	0xe8, 0xe9, 0xe6, 0xe4, 0x4b, 0x4e, 0x28, 0x2c
};

void DeviceMock::enumerateTo(KeyboardComm::DeviceList *target) {
	QSharedPointer<Device> mockKinesis = QSharedPointer<Device>(
	    new DeviceMock("Mock Kinesis",
	                   1,            // layout
	                   172,              // mapping size
	                   6, 1024,          // programs
	                   300, 1024, 4, // macros
	                   QByteArray(reinterpret_cast<const char*>(&kinesis_default_mapping[0]),
	                              sizeof(kinesis_default_mapping))));
	{
		QSharedPointer<DeviceSession> session = mockKinesis->newSession();
		session->resetFully();
	}

	QSharedPointer<Device> mockErgodox = QSharedPointer<Device>(
	    new DeviceMock("Mock Ergodox",
	                   2,            // layout
	                   152,              // mapping size
	                   6, 1024,          // programs
	                   300, 1024, 4, // macros
	                   QByteArray(reinterpret_cast<const char*>(&ergodox_default_mapping[0]),
	                              sizeof(ergodox_default_mapping))));
	{
		QSharedPointer<DeviceSession> session = mockErgodox->newSession();
		session->resetFully();
	}

	target->push_back(mockKinesis);
	target->push_back(mockErgodox);
}

uint8_t DeviceSessionMock::getLayoutID() {
	return mDevice->mLayoutID;
}
uint8_t DeviceSessionMock::getMappingSize() {
	return mDevice->mMappingSize;
}
uint8_t DeviceSessionMock::getNumPrograms() {
	return mDevice->mNumPrograms;
}
uint16_t DeviceSessionMock::getProgramSpaceRaw()  {
	return mDevice->mRawProgramSpace;
}
uint16_t DeviceSessionMock::getProgramSpace()  {
	return getProgramSpaceRaw() - 4 * getNumPrograms();
}
uint16_t DeviceSessionMock::getMacroIndexSize()  {
	return mDevice->mMacroIndexSize;
}
uint16_t DeviceSessionMock::getMacroStorageSize()  {
	return mDevice->mMacroStorageSize;
}
uint8_t DeviceSessionMock::getMacroMaxKeys()  {
	return mDevice->mMacroMaxKeys;
}
QByteArray DeviceSessionMock::getMapping() {
	return mDevice->mMapping;
}
void DeviceSessionMock::setMapping(const QByteArray& mapping) {
	mDevice->mMapping = mapping;
}
QByteArray DeviceSessionMock::getDefaultMapping() {
	return mDevice->mDefaultMapping;
}
QByteArray DeviceSessionMock::getPrograms() {
	return mDevice->mPrograms;
}
void DeviceSessionMock::setPrograms(const QByteArray& programs) {
	mDevice->mPrograms = programs;
}
QByteArray DeviceSessionMock::getMacroIndex() {
	return mDevice->mMacroIndex;
}
void DeviceSessionMock::setMacroIndex(const QByteArray& macroIndex) {
	mDevice->mMacroIndex = macroIndex;
}
QByteArray DeviceSessionMock::getMacroStorage() {
	return mDevice->mMacroStorage;
}
void DeviceSessionMock::setMacroStorage(const QByteArray& macroStorage) {
	mDevice->mMacroStorage = macroStorage;
}
void DeviceSessionMock::reset() {
	mDevice->mMapping = mDevice->mDefaultMapping;
}
void DeviceSessionMock::resetFully() {
	mDevice->mMacroStorage = QByteArray(mDevice->mMacroStorageSize, 0x00);

	mDevice->mPrograms = QByteArray(mDevice->mRawProgramSpace, 0x00);
	mDevice->mPrograms[0] = 0xff;

	mDevice->mMacroIndex = QByteArray(mDevice->mMacroIndexSize, 0x00);
	mDevice->mMacroIndex[0] = 0xff;

	this->reset();
}