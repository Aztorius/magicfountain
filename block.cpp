#include "block.h"

Block::Block(BlockType type)
{
    m_type = type;
}

Block::Block(BlockType type, QString data)
{
    m_type = type;
    m_data = data;
}

Block::~Block()
{
    qDeleteAll(m_blocks.begin(), m_blocks.end());
}

void Block::addBlock(Block *block)
{
    m_blocks.append(block);
}

BlockType Block::getType()
{
    return m_type;
}

void Block::setType(BlockType type)
{
    m_type = type;
}

QString Block::getData()
{
    return m_data;
}

QList<Block *> Block::getBlocks()
{
    return m_blocks;
}

QString Block::toHtml()
{
    QString html;

    switch (m_type) {
    case BlockType::Action:
        html.append("<p>" + m_data);
        break;
    case BlockType::Author:
        html.append("<p style=\"text-align: center;\">" + m_data);

        foreach(Block *block, m_blocks) {
            html.append("<br/>" + block->toHtml());
        }

        html.append("</p>");
        return html;
    case BlockType::BlankLine:
        html.append("<p style=\"white-space:pre-warp;\"> ");
        break;
    case BlockType::CenteredText:
        html.append("<p style=\"text-align:center;\">" + m_data);
        break;
    case BlockType::Character:
        html.append("<p style=\"margin-left: 19em;\">" + m_data);
        break;
    case BlockType::CharacterLeft:
        html.append("<p style=\"margin-left: 11em;\">" + m_data);
        break;
    case BlockType::CharacterRight:
        html.append("<p style=\"margin-left: 28em;\">" + m_data);
        break;
    case BlockType::Contact:
        html.append("<p style=\"text-align: left;\">" + m_data);

        foreach(Block *block, m_blocks) {
            html.append("<br/>" + block->toHtml());
        }

        html.append("</p>");
        return html;
    case BlockType::Credit:
        html.append("<p style=\"text-align: center;\">" + m_data);

        foreach(Block *block, m_blocks) {
            html.append("<br/>" + block->toHtml());
        }

        html.append("</p>");
        return html;
    case BlockType::Dialogue:
        html.append("<p style=\"margin-left: 12em; margin-right: 9em;\">" + m_data);
        break;
    case BlockType::DraftDate:
        html.append("<br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><p style=\"text-align: left;\">" + m_data);

        foreach(Block *block, m_blocks) {
            html.append("<br/>" + block->toHtml());
        }

        html.append("</p>");
        return html;
    case BlockType::DualDialogueLeft:
        html.append("<p style=\"margin-left: 0em; margin-right: 21em;\">" + m_data);
        break;
    case BlockType::DualDialogueRight:
        html.append("<p style=\"margin-left: 23em;\">" + m_data);
        break;
    case BlockType::Empty:
        break;
    case BlockType::Global:
        html.append("<p>");
        break;
    case BlockType::LeftParentheticals:
        html.append("<p style=\"margin-left: 3em; margin-right: 15em;\">" + m_data);
        break;
    case BlockType::Lyrics:
        html.append("<p>" + m_data);
        break;
    case BlockType::PageBreaks:
        html.append("<p style=\"white-space:pre-warp; page-break-after: always;\" > ");
        break;
    case BlockType::Parentheticals:
        html.append("<p style=\"margin-left: 15em; margin-right: 6em;\">" + m_data);
        break;
    case BlockType::RawText:
        return m_data;
    case BlockType::RightParentheticals:
        html.append("<p style=\"margin-left: 15em; margin-right: 27em;\">" + m_data);
        break;
    case BlockType::Scene:
        html.append("<p>" + m_data);
        break;
    case BlockType::Source:
        html.append("<p style=\"text-align: center;\">" + m_data);

        foreach(Block *block, m_blocks) {
            html.append("<br/>" + block->toHtml());
        }

        html.append("</p>");
        return html;
    case BlockType::Title:
        html.append("<p style=\"text-align: center;\"><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>" + m_data);

        foreach(Block *block, m_blocks) {
            html.append("<br/>" + block->toHtml());
        }

        html.append("</p>");
        return html;
    case BlockType::TitlePage:
        html.append("<p style=\"page-break-after: always;\">");
        break;
    case BlockType::Transitions:
        html.append("<p style=\"margin-left: 480px;\">" + m_data);
        break;
    default :
        html.append("<p>" + m_data);
        break;
    }

    foreach(Block *block, m_blocks) {
        html.append(block->toHtml());
    }

    html.append("</p>");

    return html;
}

Block& Block::operator=(const Block& other)
{
    m_type = other.m_type;
    m_data = other.m_data;
    m_blocks = other.m_blocks;
    return *this;
}
