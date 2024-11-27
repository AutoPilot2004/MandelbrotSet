#pragma once

#define DELETE_CPY_OP(ClassName) ClassName(const ClassName&)            = delete; \
								 ClassName& operator=(const ClassName&) = delete

#define DELETE_MOV_OP(ClassName) ClassName(ClassName&&)            = delete; \
								 ClassName& operator=(ClassName&&) = delete

#define DELETE_CPY_MOV_OP(ClassName) DELETE_CPY_OP(ClassName); \
									 DELETE_MOV_OP(ClassName)