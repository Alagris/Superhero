import re
import os


def norm_anim_name(k):
    return k.lower().replace("_", "")


class Anim:
    def __init__(self, path):
        self.path = path
        self.ue5 = None

    def load(self):
        import unreal
        if self.ue5 is None:
            self.ue5 = unreal.EditorAssetLibrary.load_asset(self.path)
        return self.ue5




class SideEffect:

    def __str__(self):
        return self.type

    def __repr__(self):
        return self.__str__()


class SideEffectAddResp(SideEffect):
    type = "ADD_RESP"
    pure = False

    def __init__(self, stage_id, resp):
        self.resp = resp
        self.stage_id = stage_id

    def __str__(self):
        return self.type + " " + self.stage_id + " " + self.resp

    def to_ue5(self, c: 'Converter', resp: 'Resp'):
        pass


class SideEffectExchange(SideEffect):
    type = "EXCHANGE"
    pure = True

    def __init__(self):
        pass

    def to_ue5(self, c: 'Converter', resp: 'Resp'):
        c.make_ue5_resp(resp.n)


class SideEffectTrade(SideEffect):
    type = "TRADE"
    pure = True

    def __init__(self):
        pass


class SideEffectSexTop(SideEffect):
    type = "SEX_TOP"
    pure = True

    def __init__(self):
        pass


class SideEffectSexBot(SideEffect):
    type = "SEX_BOT"
    pure = True

    def __init__(self):
        pass


class SideEffectWait(SideEffect):
    type = "WAIT"
    pure = True

    def __init__(self):
        pass


class SideEffectStopWait(SideEffect):
    type = "STOP_WAIT"
    pure = True

    def __init__(self):
        pass


class SideEffectFollow(SideEffect):
    type = "FOLLOW"
    pure = True

    def __init__(self):
        pass


class SideEffectStopFollow(SideEffect):
    type = "STOP_FOLLOW"
    pure = True

    def __init__(self):
        pass


class SideEffectSetFlag(SideEffect):
    type = "SET_FLAG"
    pure = False

    def __init__(self, flag: str, value: str):
        self.value = value
        self.flag = flag

    def __str__(self):
        return self.type + " " + self.flag + " " + self.value


class SideEffectSetStage(SideEffect):
    type = "SET_STAGE"
    pure = False

    def __init__(self, npc: str, stage: str):
        self.npc = npc
        self.stage = stage

    def __str__(self):
        return self.type + " " + self.npc + " " + self.stage

    def to_ue5(self, c:'Converter', resp:'Resp'):
        pass


class Npc:
    def __init__(self):
        self.name = "???"
        self.hairdo = -1
        self.hairColor = (1,1,1)
        self.secondaryHairColor = (1,1,1)
        self.skinColors:{str:(float,float,float)} = {}
        self.morphs:{str:float} = {}
        self.female = True
        self.likesFemales = 1
        self.likesMales = 1
        self.likesAnal = 1
        self.likesOral = 1
        self.likesFingering = 1
        self.likesBDSM = 1
        self.likesVaginal = 1
        self.maxHealth = 100.
        self.maxMagic = 100.
        self.maxStamina = 100.


class Stage:
    def __init__(self, name: str, file_name: str, text: str = None, anim: str = None):
        if '.' in name:
            raise Exception("Stage name " + name + " contains dot")
        self.name: str = name
        self.text: str = text
        self.anim: str = anim
        if '.' in file_name:
            raise Exception("File " + file_name + " contains dot")
        self.file_name: str = file_name
        self.responses = []
        self.ue5 = None

    def fullname(self):
        return self.file_name + '.' + self.name

    def finalize(self, next_stage_name):
        for resp in self.responses:
            resp.finalize(next_stage_name)


class Resp:
    def __init__(self, name: str, short: str = None, long: str = None, next_stage: str = None, side_effects=None,
                 condition=None, file_name: str = None):
        self.short: str = short
        self.long: str = long
        if '.' in file_name:
            raise Exception("File " + file_name + " contains dot")
        self.file_name: str = file_name
        if '.' in name:
            raise Exception("Response name " + name + " contains dot")
        self.name: str = name
        self.next_stage: str = next_stage
        self.condition: str = condition
        self.side_effects: list = side_effects
        self.ue5 = None

    def fullname(self):
        return self.file_name + '.' + self.name

    def finalize(self, next_stage_name):
        if self.long is None or self.long == "":
            self.long = self.short
        if self.next_stage is None:
            self.next_stage = next_stage_name


def strip_ext(f):
    file_name: str = os.path.basename(f)
    try:
        i = file_name.index('.')
        file_name = file_name[:i]
    except ValueError:
        pass
    return file_name


class Context:

    def __init__(self, stage: Stage = None, resp: Resp = None):
        self.current_stage = stage
        self.current_resp = resp

    def assert_invariants(self):
        assert self.current_stage is None or isinstance(self.current_stage, Stage)
        assert self.current_resp is None or isinstance(self.current_resp, Resp)


RESP_REGEX = re.compile(
    " *(?P<short_text>.*?) *(==> *(?P<next_stage>[A-Z_a-z0-9.!]+)? *(:(?P<side_effect>.*?))?(\?(?P<condition>.*))?)?[ \n\r]*")



STAGE_REGEX = re.compile(" *(--|(?P<name>[A-Za-z_0-9]+)) *(@(?P<anim>[A-Za-z_0-9]+) *)?[ \n\r]*")


class Converter:

    def __init__(self):
        self.npcs: {str: Npc} = {}
        self.anims: {str: Anim} = {}
        self.stages: {str: {str: Stage}} = {}
        self.resps: {str: {str: Resp}} = {}
        self.asset_tools = None
        self.asset_factory = None
        self.pre_content_dir = None
        self.content_dir = None

    def parse_resp(self, s, name, file_name):
        m = RESP_REGEX.fullmatch(s)
        resp_short_text = m.group('short_text')
        next_stage = m.group('next_stage')
        side_effect = m.group('side_effect')
        condition = m.group('condition')
        r = Resp(
            name=name,
            short=resp_short_text,
            long="",
            file_name=file_name,
            next_stage=next_stage,
            condition=condition,
            side_effects=[]
        )
        if side_effect is not None and len(side_effect) > 0:
            r.side_effects.append(self.parse_side_effect(side_effect))
        return r

    def parse_side_effect(self, s: str):
        parts = s.split(maxsplit=1)
        if len(parts) > 1:
            first, rest = parts
        else:
            first, = parts
            rest = ""
        if first == SideEffectAddResp.type:
            return SideEffectAddResp()
        elif first == SideEffectExchange.type:
            return SideEffectExchange()
        elif first == SideEffectTrade.type:
            return SideEffectTrade()
        elif first == SideEffectSexTop.type:
            return SideEffectSexTop()
        elif first == SideEffectSexBot.type:
            return SideEffectSexBot()
        elif first == SideEffectWait.type:
            return SideEffectWait()
        elif first == SideEffectStopWait.type:
            return SideEffectStopWait()
        elif first == SideEffectFollow.type:
            return SideEffectFollow()
        elif first == SideEffectStopFollow.type:
            return SideEffectStopFollow()
        elif first == SideEffectSetFlag.type:
            flag, value = rest.split()
            return SideEffectSetFlag(flag=flag, value=value)
        elif first == SideEffectSetStage.type:
            npc_id, stage_id = rest.split()
            self.npcs.get(npc_id)
            return SideEffectSetStage(npc=npc_id, stage=stage_id)

    def parse_npc_files(self, d):
        if os.path.exists(d):
            for f in os.listdir(d):
                self.parse_npc_file(os.path.join(d, f))

    def parse_anim_files(self, f):
        # todo
        self.anims = {}

    def parse_npc_file(self, f):
        npc = Npc()
        npc_id = strip_ext(f)
        self.npcs[npc_id] = npc
        with open(f, 'r') as f:
            GLOBAL = 0
            MORPHS = 1
            SKIN_COLORS = 2
            state = GLOBAL
            def parse_global(l:str):
                nonlocal state
                field, value = l.split(':', maxsplit=1)
                if field == 'Name':
                    npc.name = value.strip()
                elif field == 'Hairdo':
                    npc.hairdo = int(value)
                elif field == 'HairColor':
                    npc.hairColor = tuple(map(float,value.strip().split(',')))
                elif field == 'SecondaryHairColor':
                    npc.secondaryHairColor = tuple(map(float,value.strip().split(',')))
                elif field == 'SkinColors':
                    #npc.skinColors = value
                    state = SKIN_COLORS
                    return
                elif field == 'Morphs':
                    #npc.morphs = value
                    state = MORPHS
                    return
                elif field == 'Female':
                    npc.female = bool(value)
                elif field == 'LikesFemales':
                    npc.likesFemales = float(value)
                elif field == 'LikesMales':
                    npc.likesMales = float(value)
                elif field == 'LikesAnal':
                    npc.likesAnal = float(value)
                elif field == 'LikesOral':
                    npc.likesOral = float(value)
                elif field == 'LikesFingering':
                    npc.likesFingering = float(value)
                elif field == 'LikesBDSM':
                    npc.likesBDSM = float(value)
                elif field == 'LikesVaginal':
                    npc.likesVaginal = float(value)
                elif field == 'MaxHealth':
                    npc.maxHealth = float(value)
                elif field == 'MaxMagic':
                    npc.maxMagic = float(value)
                elif field == 'MaxStamina':
                    npc.maxStamina = float(value)
                state = GLOBAL

            for line_num, line in enumerate(f.readlines()):
                if state == GLOBAL:
                    parse_global(line)
                elif state == SKIN_COLORS:
                    if line.startswith("  "):
                        param_name, color = line.split(":")
                        npc.morphs[param_name.strip()] = tuple(map(float,value.strip().split(',')))
                    else:
                        parse_global(line)
                elif state == MORPHS:
                    if line.startswith("  "):
                        morph_name, value = line.split(":")
                        npc.morphs[morph_name.strip()] = float(value)
                    else:
                        parse_global(line)


    def parse_dialogue_file(self, f):
        ctx = [Context()]

        file_name = strip_ext(f)
        stages = self.stages[file_name] = {}
        resps = self.resps[file_name] = {}

        def new_stage():
            m = STAGE_REGEX.fullmatch(stripped)
            if m is None:
                raise Exception(f"Not a valid stage at line {line_num}:{stripped}")
            next_stage_name = m.group('name')
            anim = m.group('anim')
            if anim is not None:
                anim = norm_anim_name(anim)
                if anim not in self.anims:
                    raise Exception(anim + " is not a known animation")
            if next_stage_name is None:
                next_stage_name = str(len(stages))
            if ctx[-1].current_stage is not None:
                ctx[-1].current_stage.finalize(next_stage_name)
            elif ctx[-1].current_resp is not None:
                ctx[-1].current_resp.finalize(next_stage_name)
            if next_stage_name in stages:
                raise Exception("Stage " + next_stage_name + " is duplicate in " + file_name)
            stages[next_stage_name] = ctx[-1].current_stage = Stage(name=next_stage_name, text="", anim=anim,
                                                                    file_name=file_name)
            ctx[-1].current_resp = None

        with open(f, 'r') as f:

            for line_num, line in enumerate(f.readlines()):
                stripped = line.lstrip()
                if stripped.startswith('#') or stripped == "":
                    continue
                space_count = len(line) - len(stripped)
                current_depth = len(ctx) - 1
                depth = space_count // 8
                indent = space_count % 8
                ctx[-1].assert_invariants()
                while current_depth > depth:  # less spaces = end of nested state
                    ctx.pop()
                    current_depth = len(ctx) - 1
                    ctx[-1].assert_invariants()
                if current_depth == depth and indent == 0:  # no spaces = new stage beginning
                    new_stage()
                elif current_depth == depth and indent == 6 and stripped.startswith(
                        "*"):  # 6 spaces and * = Side effect
                    side_effect = self.parse_side_effect(stripped[indent + 1:].strip())
                    ctx[-1].current_resp.side_effects.append(side_effect)
                elif current_depth == depth and indent == 4 and stripped.startswith("-"):  # 4 spaces and - = response
                    stripped = stripped[1:]
                    if stripped.startswith(" "):
                        resp_name = ctx[-1].current_stage.name + "_" + str(len(ctx[-1].current_stage.responses))
                        if resp_name in resps:
                            raise Exception("Response "+resp_name+" is duplicate in "+file_name)
                        ctx[-1].current_resp = resps[resp_name] = self.parse_resp(stripped, resp_name, file_name)
                        ctx[-1].current_stage.responses.append(ctx[-1].current_resp)
                    else:
                        ctx[-1].current_resp = None
                        ctx[-1].current_stage.responses.append(stripped.strip())
                elif current_depth == depth and indent == 4:  # 4 spaces = multiline stage text
                    if len(ctx[-1].current_stage.text) > 0:
                        ctx[-1].current_stage.text += "\n"
                    ctx[-1].current_stage.text += stripped.strip()
                elif current_depth == depth and indent == 6:  # 6 spaces = long response text
                    if len(ctx[-1].current_resp.long) > 0:
                        ctx[-1].current_resp.long += "\n"
                    ctx[-1].current_resp.long += stripped.strip()
                elif current_depth + 1 == depth:  # 8 spaces = new nested state
                    ctx.append(Context(resp=ctx[-1].current_resp))
                    new_stage()
                else:
                    assert False, f"couldn't parse line {line_num}:{line}"

    def parse_dir(self, d):
        if not os.path.exists(d):
            os.makedirs(d, exist_ok=True)
        for file in os.listdir(d):
            file = os.path.join(d, file)
            if os.path.isdir(file):
                self.parse_dir(file)
            if file.endswith(".txt"):
                self.parse_dialogue_file(file)

    @staticmethod
    def parse_ref_name(ref, file_name):
        parts = ref.split('.')
        if len(parts) == 1:
            ref, = parts
        elif len(parts) == 2:
            file_name, ref = parts
        else:
            raise Exception(ref + " is not a valid identifier")
        return file_name, ref

    @staticmethod
    def find_abs_ref(database, file_name, ref_id):
        if ref_id == "!":
            return None
        file = database.get(file_name)
        if file is None:
            raise Exception(file_name + " is not a valid file")
        obj = file.get(ref_id)
        if obj is None:
            raise Exception(ref_id + " does not exist in " + file_name)
        return obj

    @staticmethod
    def find_ref(database, ref, file_name):
        next_stage_file_name, next_stage_id = Converter.parse_ref_name(ref, file_name)
        return Converter.find_abs_ref(database, next_stage_file_name, next_stage_id)

    def resolve_references(self):
        for file_name, resps in self.resps.items():
            for resp in resps.values():
                resp.next_stage = Converter.find_ref(self.stages, resp.next_stage, file_name)

    def unparse_all(self):
        for file_name, stages in self.stages.items():
            for stage in stages.values():
                print(stage.fullname() + ("" if stage.anim is None else " @" + stage.anim))
                print("    " + stage.text.replace("\n", "\\n"))
                for resp in stage.responses:
                    next_stage = "!" if resp.next_stage is None else resp.next_stage.fullname()
                    print(f"    - {resp.short} ==> {next_stage}:{resp.side_effects}?{resp.condition}")
                    print("      " + resp.long.replace("\n", "\\n"))

    def full_parse(self, content_dir, pre_content_dir):
        self.parse_anim_files(content_dir)
        self.parse_npc_files(os.path.join(pre_content_dir, 'Npc'))
        self.parse_dir(os.path.join(pre_content_dir, 'Dialogues'))
        self.resolve_references()

    def run_outside_unreal(self):
        pre_content_dir = os.path.realpath(__file__)
        self.content_dir = os.path.abspath(os.path.join(pre_content_dir, '../../Content'))
        self.pre_content_dir = os.path.abspath(os.path.dirname(pre_content_dir))
        self.full_parse(self.content_dir, self.pre_content_dir)
        self.unparse_all()

    def run_inside_unreal(self):
        import unreal
        proj_dir = os.path.abspath(unreal.Paths.project_dir())
        self.content_dir = os.path.join(proj_dir, 'Content')
        self.pre_content_dir = os.path.join(proj_dir, 'Scripts')
        self.full_parse(self.content_dir , self.pre_content_dir)
        self.unparse_all()
        self.convert_to_ue5()

    def make_or_create(self, asset_name, package_path, asset_class):
        import unreal
        p = package_path+"/"+asset_name
        if unreal.EditorAssetLibrary.does_asset_exist(p):
            return unreal.EditorAssetLibrary.load_asset(p)
        else:
            return self.asset_tools.create_asset(
                asset_name,
                package_path,
                asset_class,
                self.asset_factory
            )

    def make_ue5_resp(self, resp: Resp):
        import unreal
        resp_name = "RESP_" + resp.file_name + "_" + resp.name
        print("Creating", resp_name)
        return self.make_or_create(resp_name, "/Game/Dialogue/Responses", unreal.DialogueResponse)

    def make_ue5_stage(self, stage: Stage):
        import unreal
        stage_name = "STG_" + stage.file_name + "_" + stage.name
        return self.make_or_create(stage_name, "/Game/Dialogue/Stages", unreal.DialogueStage)

    def convert_to_ue5(self):
        import unreal
        self.asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
        self.asset_factory = unreal.DataAssetFactory()
        for resps in self.resps.values():
            for resp in resps.values():
                resp.ue5 = self.make_ue5_resp(resp)
                if resp.ue5 is None:
                    print("ERROR:", resp.file_name, resp.name, "failed creating")
                resp.ue5.player_text = unreal.Text(resp.short)
        for stages in self.stages.values():
            for stage in stages.values():
                stage.ue5 = self.make_ue5_stage(stage)
                stage.ue5.npc_text = unreal.Text(stage.text)
                stage.ue5.responses = [r.ue5 for r in stage.responses]
                if stage.anim is not None:
                    anim = self.anims[stage.anim].load()
                    stage.ue5.animation = anim
        for resps in self.resps.values():
            for resp in resps.values():
                assert isinstance(resp, Resp)
                if resp.next_stage is not None:
                    assert isinstance(resp.next_stage, Stage)
                    assert resp.next_stage.ue5 is not None
                    resp.ue5.next = resp.next_stage.ue5
                unreal.EditorAssetLibrary.save_loaded_asset(resp.ue5)
        for stages in self.stages.values():
            for stage in stages.values():
                unreal.EditorAssetLibrary.save_loaded_asset(stage.ue5)


if "PYCHARM_HOSTED" in os.environ:
    Converter().run_outside_unreal()
else:
    Converter().run_inside_unreal()
