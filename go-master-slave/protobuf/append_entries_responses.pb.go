// Code generated by protoc-gen-go.
// source: append_entries_responses.proto
// DO NOT EDIT!

package protobuf

import proto "github.com/golang/protobuf/proto"
import fmt "fmt"
import math "math"

// Reference imports to suppress errors if they are not otherwise used.
var _ = proto.Marshal
var _ = fmt.Errorf
var _ = math.Inf

type AppendEntriesResponse struct {
	Term             *uint64 `protobuf:"varint,1,req,name=Term" json:"Term,omitempty"`
	Index            *uint64 `protobuf:"varint,2,req,name=Index" json:"Index,omitempty"`
	CommitIndex      *uint64 `protobuf:"varint,3,req,name=CommitIndex" json:"CommitIndex,omitempty"`
	Success          *bool   `protobuf:"varint,4,req,name=Success" json:"Success,omitempty"`
	XXX_unrecognized []byte  `json:"-"`
}

func (m *AppendEntriesResponse) Reset()                    { *m = AppendEntriesResponse{} }
func (m *AppendEntriesResponse) String() string            { return proto.CompactTextString(m) }
func (*AppendEntriesResponse) ProtoMessage()               {}
func (*AppendEntriesResponse) Descriptor() ([]byte, []int) { return fileDescriptor1, []int{0} }

func (m *AppendEntriesResponse) GetTerm() uint64 {
	if m != nil && m.Term != nil {
		return *m.Term
	}
	return 0
}

func (m *AppendEntriesResponse) GetIndex() uint64 {
	if m != nil && m.Index != nil {
		return *m.Index
	}
	return 0
}

func (m *AppendEntriesResponse) GetCommitIndex() uint64 {
	if m != nil && m.CommitIndex != nil {
		return *m.CommitIndex
	}
	return 0
}

func (m *AppendEntriesResponse) GetSuccess() bool {
	if m != nil && m.Success != nil {
		return *m.Success
	}
	return false
}

func init() {
	proto.RegisterType((*AppendEntriesResponse)(nil), "protobuf.AppendEntriesResponse")
}

var fileDescriptor1 = []byte{
	// 131 bytes of a gzipped FileDescriptorProto
	0x1f, 0x8b, 0x08, 0x00, 0x00, 0x09, 0x6e, 0x88, 0x02, 0xff, 0xe2, 0x92, 0x4b, 0x2c, 0x28, 0x48,
	0xcd, 0x4b, 0x89, 0x4f, 0xcd, 0x2b, 0x29, 0xca, 0x4c, 0x2d, 0x8e, 0x2f, 0x4a, 0x2d, 0x2e, 0xc8,
	0xcf, 0x2b, 0x4e, 0x2d, 0xd6, 0x2b, 0x28, 0xca, 0x2f, 0xc9, 0x17, 0xe2, 0x00, 0x53, 0x49, 0xa5,
	0x69, 0x4a, 0x51, 0x5c, 0xa2, 0x8e, 0x60, 0xb5, 0xae, 0x10, 0xa5, 0x41, 0x50, 0x95, 0x42, 0x3c,
	0x5c, 0x2c, 0x21, 0xa9, 0x45, 0xb9, 0x12, 0x8c, 0x0a, 0x4c, 0x1a, 0x2c, 0x42, 0xbc, 0x5c, 0xac,
	0x9e, 0x79, 0x29, 0xa9, 0x15, 0x12, 0x4c, 0x60, 0xae, 0x30, 0x17, 0xb7, 0x73, 0x7e, 0x6e, 0x6e,
	0x66, 0x09, 0x44, 0x90, 0x19, 0x2c, 0xc8, 0xcf, 0xc5, 0x1e, 0x5c, 0x9a, 0x9c, 0x9c, 0x5a, 0x5c,
	0x2c, 0xc1, 0x02, 0x14, 0xe0, 0x00, 0x04, 0x00, 0x00, 0xff, 0xff, 0xe1, 0x6a, 0xc1, 0xa6, 0x86,
	0x00, 0x00, 0x00,
}