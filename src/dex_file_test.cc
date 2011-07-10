// Copyright 2011 Google Inc. All Rights Reserved.

#include "src/dex_file.h"
#include "src/object.h"
#include "src/scoped_ptr.h"

#include <stdio.h>
#include "gtest/gtest.h"

namespace art {

// class Nested {
//     class Inner {
//     }
// }
static const char kNestedDex[] =
  "ZGV4CjAzNQAQedgAe7gM1B/WHsWJ6L7lGAISGC7yjD2IAwAAcAAAAHhWNBIAAAAAAAAAAMQCAAAP"
  "AAAAcAAAAAcAAACsAAAAAgAAAMgAAAABAAAA4AAAAAMAAADoAAAAAgAAAAABAABIAgAAQAEAAK4B"
  "AAC2AQAAvQEAAM0BAADXAQAA+wEAABsCAAA+AgAAUgIAAF8CAABiAgAAZgIAAHMCAAB5AgAAgQIA"
  "AAIAAAADAAAABAAAAAUAAAAGAAAABwAAAAkAAAAJAAAABgAAAAAAAAAKAAAABgAAAKgBAAAAAAEA"
  "DQAAAAAAAQAAAAAAAQAAAAAAAAAFAAAAAAAAAAAAAAAAAAAABQAAAAAAAAAIAAAAiAEAAKsCAAAA"
  "AAAAAQAAAAAAAAAFAAAAAAAAAAgAAACYAQAAuAIAAAAAAAACAAAAlAIAAJoCAAABAAAAowIAAAIA"
  "AgABAAAAiAIAAAYAAABbAQAAcBACAAAADgABAAEAAQAAAI4CAAAEAAAAcBACAAAADgBAAQAAAAAA"
  "AAAAAAAAAAAATAEAAAAAAAAAAAAAAAAAAAEAAAABAAY8aW5pdD4ABUlubmVyAA5MTmVzdGVkJElu"
  "bmVyOwAITE5lc3RlZDsAIkxkYWx2aWsvYW5ub3RhdGlvbi9FbmNsb3NpbmdDbGFzczsAHkxkYWx2"
  "aWsvYW5ub3RhdGlvbi9Jbm5lckNsYXNzOwAhTGRhbHZpay9hbm5vdGF0aW9uL01lbWJlckNsYXNz"
  "ZXM7ABJMamF2YS9sYW5nL09iamVjdDsAC05lc3RlZC5qYXZhAAFWAAJWTAALYWNjZXNzRmxhZ3MA"
  "BG5hbWUABnRoaXMkMAAFdmFsdWUAAgEABw4AAQAHDjwAAgIBDhgBAgMCCwQADBcBAgQBDhwBGAAA"
  "AQEAAJAgAICABNQCAAABAAGAgATwAgAAEAAAAAAAAAABAAAAAAAAAAEAAAAPAAAAcAAAAAIAAAAH"
  "AAAArAAAAAMAAAACAAAAyAAAAAQAAAABAAAA4AAAAAUAAAADAAAA6AAAAAYAAAACAAAAAAEAAAMQ"
  "AAACAAAAQAEAAAEgAAACAAAAVAEAAAYgAAACAAAAiAEAAAEQAAABAAAAqAEAAAIgAAAPAAAArgEA"
  "AAMgAAACAAAAiAIAAAQgAAADAAAAlAIAAAAgAAACAAAAqwIAAAAQAAABAAAAxAIAAA==";

TEST(DexFile, Open) {
  scoped_ptr<DexFile> dex(DexFile::OpenBase64(kNestedDex));
  ASSERT_TRUE(dex != NULL);
}

TEST(DexFile, LoadNonexistent) {
  scoped_ptr<DexFile> dex(DexFile::OpenBase64(kNestedDex));
  ASSERT_TRUE(dex != NULL);

  scoped_ptr<Class> klass(reinterpret_cast<Class*>(new byte[sizeof(Class)]));
  bool result = dex->LoadClass("NoSuchClass", klass.get());
  ASSERT_FALSE(result);
}

TEST(DexFile, Load) {
  scoped_ptr<DexFile> dex(DexFile::OpenBase64(kNestedDex));
  ASSERT_TRUE(dex != NULL);

  scoped_ptr<Class> klass(reinterpret_cast<Class*>(new byte[sizeof(Class)]));
  bool result = dex->LoadClass("LNested;", klass.get());
  ASSERT_TRUE(result);

  uint32_t vmeth = klass->NumVirtualMethods();
  EXPECT_EQ(vmeth, 0U);

  uint32_t dmeth = klass->NumDirectMethods();
  EXPECT_EQ(dmeth, 1U);
}

}  // namespace art
