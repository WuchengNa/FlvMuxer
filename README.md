FLV Format:
|FLV Header|footer|FLV Tag Header|FLV Tag Body|...|

__FLV Header Struct__
| 1 byte "F" | signature
| 1 byte "L" | signature
| 1 byte "V" | signature
| 1 byte 0x01 | version 1
| 5 bit 00000 | TypeFlags Reserved must be 0
| 1 bit 0 or 1 | TypeFlags boHasAudio Tag
| 1 bit 0 | TypeFlags Reserved must be 0
| 1 bit 0 or 1 | TypeFlags boHasVideo Tag 
| 4 byte | Header size, (Always be 9)

__FLV Body Struct__
| 4   byte | pervious tag size
| 11  byte | tag header
| ... byte | tag body (data)

__FLV TAG Header Struct__
| 2 bit | Reserved for FMS, Always be 0
| 1 bit | Filter，Always be 0
| 5 bit | Tag Types, Audio:8/ video:9/ script:18
| 3 byte | Tag body size
| 3 byte | Timestamp
| 1 byte | Timestamp Extended
| 3 byte | steamID, Always be 0

__FLV TAG Body Struct__
| ... byte | body payload data

