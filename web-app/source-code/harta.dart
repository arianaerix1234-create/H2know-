import '/flutter_flow/flutter_flow_theme.dart';
import '/flutter_flow/flutter_flow_util.dart';
import '/flutter_flow/flutter_flow_web_view.dart';
import '/flutter_flow/flutter_flow_widgets.dart';
import 'dart:ui';
import 'package:flutter/material.dart';
import 'package:font_awesome_flutter/font_awesome_flutter.dart';
import 'package:google_fonts/google_fonts.dart';
import 'package:provider/provider.dart';

import 'harta_model.dart';
export 'harta_model.dart';

class HartaWidget extends StatefulWidget {
  const HartaWidget({super.key});

  static String routeName = 'harta';
  static String routePath = '/harta';

  @override
  State<HartaWidget> createState() => _HartaWidgetState();
}

class _HartaWidgetState extends State<HartaWidget> {
  late HartaModel _model;

  final scaffoldKey = GlobalKey<ScaffoldState>();

  @override
  void initState() {
    super.initState();
    _model = createModel(context, () => HartaModel());

    WidgetsBinding.instance.addPostFrameCallback((_) => safeSetState(() {}));
  }

  @override
  void dispose() {
    _model.dispose();

    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: () {
        FocusScope.of(context).unfocus();
        FocusManager.instance.primaryFocus?.unfocus();
      },
      child: Scaffold(
        key: scaffoldKey,
        backgroundColor: FlutterFlowTheme.of(context).primaryBackground,
        body: Column(
          mainAxisSize: MainAxisSize.max,
          children: [
            Stack(
              children: [
                FlutterFlowWebView(
                  content: 'https://sensational-starship-0aaf37.netlify.app/',
                  bypass: false,
                  height: 794.32,
                  verticalScroll: false,
                  horizontalScroll: false,
                ),
              ],
            ),
          ],
        ),
      ),
    );
  }
}
