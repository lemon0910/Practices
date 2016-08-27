package lemon

import "io"

type Command interface {
	CommandName() string
}

type WriteCommand struct {
	Key   string
	Value string
}

type CommandEncoder interface {
	Encode(w io.Writer) error
	Decode(r io.Reader) error
}

func (c *WriteCommand) CommandName() string {
	return "write"
}
