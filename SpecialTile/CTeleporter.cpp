#include "stdafx.h"
#include "CTeleporter.h"

CTeleporter::CTeleporter(TeleporterAttributes attributes, bool visible, bool open) {
	m_attributes = attributes;
	m_isVisible = visible;
	m_open = open;
}